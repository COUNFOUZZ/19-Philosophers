/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabda <aabda@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 13:47:56 by aabda             #+#    #+#             */
/*   Updated: 2023/03/07 00:12:30 by aabda            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <limits.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdatomic.h>
# include "errors.h"

# define FORK	"\033[0;33mhas taken a fork\033[0;0m\n"
# define EAT	"\033[0;32mis eating\033[0;0m\n"
# define SLEEP	"\033[0;35mis sleeping\033[0;0m\n"
# define THINK	"\033[0;36mis thinking\033[0;0m\n"
# define DIE	"\033[0;31mdied\033[0;0m\n"

typedef struct s_params
{
	int				nbr_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat;
	atomic_int		*someone_died;
	atomic_int		*full_eaten;
	time_t			start_time;
	pthread_mutex_t	*death;
	pthread_mutex_t	*write;
}	t_params;

typedef struct s_philo
{
	int				philo_id;
	int				eat_count;
	atomic_long		last_meal;
	pthread_t		thread_id;
	pthread_mutex_t	*fork;
	t_params		params;
	struct s_philo	*next;
	struct s_philo	*prev;
}	t_philo;

typedef struct s_global
{
	int				err_check;
	struct s_params	params;
	struct s_philo	*philo;
}	t_global;

/*		../srcs/libft_utils.c		*/
size_t	ft_strlen(const char *s);
void	ft_putstr_fd(int fd, const char *s);
int		ft_atoi(const char *str);

/*		../srcs/utils.c		*/
int		ft_init_struct(t_global *g, int argc, const char **argv);

/*		../srcs/add_philo.c		*/
int		ft_add_philo(t_global *g, int philo_nbr);
void	ft_add_prev_for_first_and_last(t_global *g);
void	ft_print_lst(t_global *g);

/*		../srcs/thread.c		*/
int		ft_threads_init(t_global *g);
int		ft_threads_join(t_global *g);

/*		../srcs/time.c		*/
time_t	ft_get_time_in_ms(t_global *g);
void	ft_sleep(t_params params, time_t time);

/*		../srcs/routine.c		*/
void	ft_philo_checker(t_global *g);
void	ft_routine(t_philo *current);

/*		../srcs/philo_utils.c		*/
void	ft_philo_checker(t_global *g);

/*		../srcs/error.c		*/
int		ft_error(t_global *g, int res);
void	ft_free_struct(t_global *g);
void	ft_free_philo(t_global *g);

#endif