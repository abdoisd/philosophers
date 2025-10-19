/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aisdaoun <aisdaoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 20:05:30 by aisdaoun          #+#    #+#             */
/*   Updated: 2025/01/24 18:22:35 by aisdaoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

long	get_curr_time_(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	print_message_(t_program *program, int philo_id, char *action)
{
	long	time;

	sem_wait(program->write_sem);
	time = get_curr_time_() - program->start_time;
	printf(GREEN"%ld"RESET" %d %s\n", time, philo_id, action);
	sem_post(program->write_sem);
}

void	ft_usleep(size_t mls)
{
	size_t	start;

	start = get_curr_time_();
	while (get_curr_time_() - start < mls)
		usleep(500);
}
