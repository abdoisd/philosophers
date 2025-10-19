/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aisdaoun <aisdaoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 15:44:34 by aisdaoun          #+#    #+#             */
/*   Updated: 2025/01/24 15:44:34 by aisdaoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_curr_time_(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	print_message_(t_program *program, int philo_id, char *action)
{
	long	time;

	pthread_mutex_lock(&program->write_lock);
	time = get_curr_time_() - program->start_time;
	printf(GREEN"%ld"RESET" %d %s\n", time, philo_id, action);
	pthread_mutex_unlock(&program->write_lock);
}

void	free_all_(t_program *program, int iter)
{
	if (iter == -1)
	{
		pthread_mutex_destroy(&program->one_by_one);
	}
	if (iter == -2)
	{
		pthread_mutex_destroy(&program->one_by_one);
		pthread_mutex_destroy(&program->iter_lock);
	}
	if (iter >= 0)
	{
		while (iter--)
			pthread_mutex_destroy(&program->forks[iter]);
		pthread_mutex_destroy(&program->one_by_one);
		pthread_mutex_destroy(&program->iter_lock);
		pthread_mutex_destroy(&program->write_lock);
	}
}

void	ft_usleep(size_t mls)
{
	size_t	start;

	start = get_curr_time_();
	while (get_curr_time_() - start < mls)
		usleep(500);
}
