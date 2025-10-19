/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   program_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aisdaoun <aisdaoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 20:10:01 by aisdaoun          #+#    #+#             */
/*   Updated: 2025/01/24 20:05:21 by aisdaoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*die_checker_thread_(void *ptr)
{
	t_program	*program;
	t_philo		*philo;

	program = ptr;
	philo = &program->philos[program->iter];
	while (1)
	{
		sem_wait(program->last_meal_sem);
		if (get_curr_time_() - philo->last_meal > program->time_to_die)
		{
			sem_wait(program->write_sem);
			printf(GREEN"%ld"RESET" %d "RED"died\n"RESET,
				get_curr_time_() - philo->last_meal, philo->id);
			exit(DIED);
		}
		sem_post(program->last_meal_sem);
	}
	return (NULL);
}

void	philo_process_(t_program *program)
{
	t_philo		*philo;
	pthread_t	die_checker;

	philo = &program->philos[program->iter];
	if (pthread_create(&die_checker, NULL, &die_checker_thread_, program) != 0
		|| pthread_detach(die_checker) != 0)
		(printf("thread error\n"), exit(EXIT_FAILURE));
	while (1)
	{
		sem_wait(program->forks_sem);
		print_message_(program, philo->id, "has taken a fork");
		print_message_(program, philo->id, "has taken a fork");
		print_message_(program, philo->id, "is eating");
		sem_wait(program->last_meal_sem);
		philo->last_meal = get_curr_time_();
		sem_post(program->last_meal_sem);
		ft_usleep(program->time_to_eat);
		philo->meals_eaten++;
		if (philo->meals_eaten >= program->each_philo_must_eat)
			sem_post(program->all_ate_sem);
		sem_post(program->forks_sem);
		print_message_(program, philo->id, "is sleeping");
		ft_usleep(program->time_to_sleep);
		print_message_(program, philo->id, "is thinking");
	}
}

void	kill_pids_(t_program *program, int count)
{
	int	i;

	i = -1;
	while (++i < count)
		kill(program->pids[i], SIGKILL);
}

void	*all_ate_thread_(void *ptr)
{
	t_program	*program;
	int			num_finished;

	program = ptr;
	num_finished = 0;
	while (1)
	{
		sem_wait(program->all_ate_sem);
		num_finished++;
		if (num_finished >= program->philos_nbr)
		{
			sem_wait(program->write_sem);
			kill_pids_(program, program->philos_nbr);
			close_sems_(program);
			exit(EXIT_SUCCESS);
		}
	}
	return (NULL);
}

void	program_bonus_(t_program *program)
{
	int			i;
	int			status;
	pthread_t	all_ate_thread;

	if (program->each_philo_must_eat != -1
		&& (pthread_create(&all_ate_thread, NULL,
				&all_ate_thread_, program) != 0
			|| pthread_detach(all_ate_thread) != 0))
		return ;
	i = -1;
	while (++i < program->philos_nbr)
	{
		program->pids[i] = fork();
		if (program->pids[i] == -1)
			return (kill_pids_(program, i));
		if (program->pids[i] == 0)
		{
			program->iter = i;
			philo_process_(program);
		}
	}
	waitpid(-1, &status, 0);
	kill_pids_(program, program->philos_nbr);
	(close_sems_(program), exit(status));
}
