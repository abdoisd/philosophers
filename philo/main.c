/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aisdaoun <aisdaoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 18:03:30 by aisdaoun          #+#    #+#             */
/*   Updated: 2025/01/24 18:03:30 by aisdaoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_mutexes_(t_program *program)
{
	int	i;

	if (pthread_mutex_init(&program->one_by_one, NULL) != 0)
		return (1);
	if (pthread_mutex_init(&program->iter_lock, NULL) != 0)
		return (free_all_(program, -1), 1);
	if (pthread_mutex_init(&program->write_lock, NULL) != 0)
		return (free_all_(program, -2), 1);
	i = -1;
	while (++i < program->philos_nbr)
	{
		if (pthread_mutex_init(&program->forks[i], NULL) != 0)
			return (free_all_(program, i), 1);
	}
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
		philos[i].right_fork = &program->forks[i];
		if (i == 0)
			philos[i].left_fork = &program->forks[program->philos_nbr - 1];
		else
			philos[i].left_fork = &program->forks[i - 1];
	}
}

int	init_program_(t_program *program)
{
	if (init_mutexes_(program) == 1)
		return (1);
	init_philos_(program);
	(*program).start_time = get_curr_time_();
	return (0);
}

int	set_args_(int argc, t_program *program, char **args)
{
	if ((argc - 1) != 4 && (argc - 1) != 5)
		return (printf(RED"invalid number of args\n"RESET), 1);
	program->philos_nbr = c_stoi_(args[0]);
	if (program->philos_nbr > 200)
		return (printf(RED"invalid args\n"RESET), 1);
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

int	main(int argc, char **argv)
{
	t_program	program;
	int			ret_val;
	int			ret_status;

	ret_status = 0;
	ret_val = set_args_(argc, &program, argv + 1);
	if (ret_val == 1)
		return (1);
	if (ret_val == 'e')
		return (0);
	if (init_program_(&program) == 1)
		return (1);
	if (program_(&program) == 1)
		ret_status = 1;
	free_all_(&program, program.philos_nbr);
	return (ret_status);
}
