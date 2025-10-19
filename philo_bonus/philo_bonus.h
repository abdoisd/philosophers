/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aisdaoun <aisdaoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 19:41:38 by aisdaoun          #+#    #+#             */
/*   Updated: 2025/01/24 20:03:24 by aisdaoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <semaphore.h>
# include <signal.h>
# include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <semaphore.h>
#include <sys/wait.h>

# define RESET		"\033[0m"
# define RED		"\033[31m"
# define GREEN		"\033[32m"

# define STOI_F		10000000000

# define ATE		0
# define DIED		1

typedef struct s_philo
{
	int				id;
	long			last_meal;
	int				meals_eaten;
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
	int				iter;
	sem_t			*forks_sem;
	sem_t			*last_meal_sem;
	sem_t			*write_sem;
	sem_t			*all_ate_sem;
	int				pids[200];
}	t_program;

// === Main ===
void	close_sems_(t_program *program);

// === Program ===
void	program_bonus_(t_program *program);

// === Utils ===
long	get_curr_time_(void);
void	print_message_(t_program *program, int philo_id, char *action);
void	ft_usleep(size_t mls);

// === Str_utils ===
long	c_stoi_(char *arg);

#endif
