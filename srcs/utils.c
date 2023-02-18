/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabda <aabda@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 20:05:24 by aabda             #+#    #+#             */
/*   Updated: 2023/02/18 23:33:23 by aabda            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

time_t	ft_get_time_in_ms(t_global *g)
{
	struct timeval	current_time;

	if (gettimeofday(&current_time, NULL) < 0)
	{
		g->err_check = -10;
		return (g->err_check);
	}
	return ((current_time.tv_sec * 1000) + (current_time.tv_usec / 1000));
}

static void	ft_check_args_error(t_global *g)
{
	if (!g->params.nbr_philo || g->params.nbr_philo <= 0)
	{
		g->err_check = -2;
		return ;
	}
	if (!g->params.time_to_die || g->params.time_to_die <= 0)
	{
		g->err_check = -3;
		return ;
	}
	if (!g->params.time_to_eat || g->params.time_to_eat <= 0)
	{
		g->err_check = -4;
		return ;
	}
	if (!g->params.time_to_sleep || g->params.time_to_sleep <= 0)
	{
		g->err_check = -5;
		return ;
	}
	if (g->params.must_eat && g->params.must_eat <= 0)
	{
		g->err_check = -6;
		return ;
	}
}

static int	ft_parse_args(t_global *g, int argc, const char **argv)
{
	g->philo = NULL;
	g->err_check = 0;
	g->params.nbr_philo = ft_atoi(argv[1]);
	g->params.time_to_die = ft_atoi(argv[2]);
	g->params.time_to_eat = ft_atoi(argv[3]);
	g->params.time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		g->params.must_eat = ft_atoi(argv[5]);
	ft_check_args_error(g);
	return (g->err_check);
}

static int	ft_philo_init(t_global *g)
{
	int	i;

	i = -1;
	while (++i < g->params.nbr_philo)
		if (ft_add_philo(g, i) != 0)
			return (g->err_check);
	ft_add_prev_for_first_and_last(g);
	return (g->err_check);
}

int	ft_init_struct(t_global *g, int argc, const char **argv)
{
	if (ft_parse_args(g, argc, argv) < 0)
		return (g->err_check);
	if (ft_philo_init(g) < 0)
		return (g->err_check);
	if (ft_threads_init(g) < 0)
		return (g->err_check);
	if (ft_threads_join(g) < 0)
		return (g->err_check);
	ft_print_lst(g);
	return (g->err_check);
}
