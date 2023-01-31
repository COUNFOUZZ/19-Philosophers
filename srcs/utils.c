/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabda <aabda@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 20:05:24 by aabda             #+#    #+#             */
/*   Updated: 2023/01/31 20:28:25 by aabda            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

static int	ft_parse_args(t_global *g, const char **argv)
{
	g->philo = NULL;
	g->err_check = 0;
	g->params.nbr_philo = ft_atoi(argv[1]);
	g->params.time_to_die = ft_atoi(argv[2]);
	g->params.time_to_eat = ft_atoi(argv[3]);
	g->params.time_to_sleep = ft_atoi(argv[4]);
	g->params.must_eat = ft_atoi(argv[5]);
	return (g->err_check);
}

static void	ft_check_args(t_global *g)
{
	int	i;

	i = -1;
	if (g->params.nbr_philo <= 0)
	{
		g->err_check = -2;
		return ;
	}
	else
	{
		while (++i < g->params.nbr_philo)
			ft_add_philo(g, i);
		ft_add_prev_for_first_and_last(g);
	}
}

int	ft_init_struct(t_global *g, const char **argv)
{
	if (ft_parse_args(g, argv) < 0)
		return (g->err_check);
	ft_check_args(g);
	ft_print_lst(g);
	// printf("1 = %d\n2 = %d\n3 = %d\n4 = %d\n5 = %d\n", g->params.nbr_philo, g->params.time_to_die, g->params.time_to_eat, g->params.time_to_sleep, g->params.must_eat);
}
