/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabda <aabda@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 13:47:56 by aabda             #+#    #+#             */
/*   Updated: 2023/02/13 21:34:29 by aabda            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <unistd.h>
# include <stdlib.h>
# include <limits.h>
# include <pthread.h>
# include "errors.h"

// Need to be delete
# include <stdio.h>

typedef struct s_params
{
	int	nbr_philo;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	must_eat;
}	t_params;

typedef struct s_philo
{
	int				philo_id;
	pthread_t		thread_id;
	pthread_mutex_t	*fork;
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

#endif