/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabda <aabda@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 20:05:24 by aabda             #+#    #+#             */
/*   Updated: 2023/02/13 22:15:51 by aabda            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

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
	ft_print_lst(g);
	return (g->err_check);
}
