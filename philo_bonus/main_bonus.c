/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aisdaoun <aisdaoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 19:43:33 by aisdaoun          #+#    #+#             */
/*   Updated: 2025/01/24 18:24:30 by aisdaoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	set_args_(int argc, t_program *program, char **args)
{
	if ((argc - 1) != 4 && (argc - 1) != 5)
		return (printf(RED"invalid number of args\n"RESET), 1);
	program->philos_nbr = c_stoi_(args[0]);
	program->time_to_die = c_stoi_(args[1]);
	program->time_to_eat = c_stoi_(args[2]);
	program->time_to_sleep = c_stoi_(args[3]);
	if (args[4] != NULL)
	{
		program->each_philo_must_eat = c_stoi_(args[4]);
		if (program->each_philo_must_eat < 0)
			return (1);
	}
	else
		program->each_philo_must_eat = -1;
	if (program->philos_nbr < 0 || program->time_to_die < 0
		|| program->time_to_eat < 0 || program->time_to_sleep < 0)
		return (1);
	if (program->philos_nbr == 0 || program->each_philo_must_eat == 0)
		return ('e');
	return (0);
}

void	init_philos_(t_program *program)
{
	int		i;
	t_philo	*philos;

	philos = program->philos;
	i = -1;
	while (++i < program->philos_nbr)
	{
		philos[i].id = i + 1;
		philos[i].last_meal = get_curr_time_();
		philos[i].meals_eaten = 0;
	}
}

void	close_sems_(t_program *program)
{
	if (program->forks_sem != SEM_FAILED)
		sem_close(program->forks_sem);
	if (program->last_meal_sem != SEM_FAILED)
		sem_close(program->last_meal_sem);
	if (program->write_sem != SEM_FAILED)
		sem_close(program->write_sem);
	if (program->forks_sem != SEM_FAILED)
		sem_close(program->forks_sem);
}

int	init_program_(t_program *program)
{
	program->forks_sem = sem_open("/forks_sem", O_CREAT | O_EXCL,
			0644, program->philos_nbr / 2);
	program->last_meal_sem = sem_open("/last_meal_sem",
			O_CREAT | O_EXCL, 0644, 1);
	program->write_sem = sem_open("/write_sem", O_CREAT | O_EXCL, 0644, 1);
	program->all_ate_sem = sem_open("/all_ate_sem", O_CREAT | O_EXCL, 0644, 0);
	if (program->forks_sem == SEM_FAILED || program->last_meal_sem == SEM_FAILED
		|| program->write_sem == SEM_FAILED
		|| program->all_ate_sem == SEM_FAILED)
		return (close_sems_(program), 1);
	if (sem_unlink("/forks_sem") == -1 || sem_unlink("/last_meal_sem") == -1
		|| sem_unlink("/all_ate_sem") == -1 || sem_unlink("/write_sem") == -1)
		return (close_sems_(program), 1);
	init_philos_(program);
	program->start_time = get_curr_time_();
	return (0);
}

int	main(int argc, char **argv)
{
	t_program	program;
	int			ret_val;

	ret_val = set_args_(argc, &program, argv + 1);
	if (ret_val == 1)
		return (1);
	if (ret_val == 'e')
		return (0);
	if (init_program_(&program) == 1)
		return (1);
	program_bonus_(&program);
	close_sems_(&program);
	exit(EXIT_FAILURE);
}
