/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aisdaoun <aisdaoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 15:45:09 by aisdaoun          #+#    #+#             */
/*   Updated: 2025/01/24 15:45:09 by aisdaoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <unistd.h>

// colors
# define RESET    "\033[0m"
# define RED      "\033[31m"
# define GREEN    "\033[32m"

# define STOI_F		10000000000

typedef struct s_philo
{
	int				id;
	pthread_t		thread;
	long			last_meal;
	int				meals_eaten;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*left_fork;
}	t_philo;

typedef struct s_program
{
	long			start_time;
	int				philos_nbr;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				each_philo_must_eat;
	t_philo			philos[200];
	pthread_mutex_t	forks[200];
	pthread_mutex_t	one_by_one;
	int				iter;
	pthread_mutex_t	iter_lock;
	pthread_mutex_t	write_lock;
}	t_program;

// === program ===
int		program_(t_program *program);

// === utils ===
long	get_curr_time_(void);
void	print_message_(t_program *program, int philo_id, char *action);
void	free_all_(t_program *program, int iter);
void	ft_usleep(size_t mls);

// === Str_utils ===
long	c_stoi_(char *arg);

#endif
