/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   program.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aisdaoun <aisdaoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 15:44:57 by aisdaoun          #+#    #+#             */
/*   Updated: 2025/01/24 15:44:57 by aisdaoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	all_ate_(t_program *program)
{
	int	i;

	i = -1;
	while (++i < program->philos_nbr)
	{
		pthread_mutex_lock(&program->one_by_one);
		if (program->philos[i].meals_eaten < program->each_philo_must_eat)
		{
			pthread_mutex_unlock(&program->one_by_one);
			return (0);
		}
		pthread_mutex_unlock(&program->one_by_one);
	}
	return (1);
}

void	*monitor_(void *data)
{
	t_program	*program;
	t_philo		*philos;
	int			i;

	program = (t_program *)data;
	philos = program->philos;
	while (1)
	{
		i = -1;
		while (++i < program->philos_nbr)
		{
			pthread_mutex_lock(&program->one_by_one);
			if (get_curr_time_() - philos[i].last_meal > program->time_to_die)
			{
				pthread_mutex_lock(&program->write_lock);
				printf(RED"%ld philo %d died\n"RESET,
					get_curr_time_() - philos[i].last_meal, philos[i].id);
				return (ft_usleep(200), NULL);
			}
			pthread_mutex_unlock(&program->one_by_one);
		}
		if (program->each_philo_must_eat != -1 && all_ate_(program))
			return (NULL);
	}
	return (NULL);
}

void	philo_routine_h_(t_philo *philo, t_program *program)
{
	pthread_mutex_lock((*philo).right_fork);
	print_message_(program, (*philo).id, "has taken a fork");
	pthread_mutex_lock((*philo).left_fork);
	print_message_(program, philo->id, "has taken a fork");
	pthread_mutex_lock(&program->one_by_one);
	print_message_(program, philo->id, "is eating");
	philo->last_meal = get_curr_time_();
	philo->meals_eaten++;
	pthread_mutex_unlock(&program->one_by_one);
	ft_usleep(program->time_to_eat);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
	print_message_(program, philo->id, "is sleeping");
	ft_usleep(program->time_to_sleep);
	print_message_(program, philo->id, "is thinking");
}

void	*philo_routine_(void *data)
{
	t_program	*program;
	t_philo		*philo;
	int			iter;

	program = (t_program *)data;
	pthread_mutex_lock(&program->iter_lock);
	iter = program->iter++;
	pthread_mutex_unlock(&program->iter_lock);
	if (iter % 2 == 1)
		ft_usleep(1);
	philo = &program->philos[iter];
	while (1)
		philo_routine_h_(philo, program);
}

int	program_(t_program *program)
{
	int			i;
	pthread_t	monitor;
	t_philo		*philos;

	program->iter = 0;
	philos = program->philos;
	if (pthread_create(&monitor, NULL, &monitor_, program) != 0)
		return (1);
	i = -1;
	while (++i < program->philos_nbr)
		if (pthread_create(&philos[i].thread, NULL,
				&philo_routine_, program) != 0)
			return (1);
	if (pthread_join(monitor, NULL) != 0)
		return (1);
	i = -1;
	while (++i < program->philos_nbr)
		if (pthread_detach(philos[i].thread) != 0)
			return (1);
	return (0);
}
