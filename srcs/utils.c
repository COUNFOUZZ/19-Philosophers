/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabda <aabda@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 20:05:24 by aabda             #+#    #+#             */
/*   Updated: 2023/03/03 15:15:38 by aabda            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

static void	ft_check_args_error(t_global *g, int argc)
{
	if (!g->params.nbr_philo || g->params.nbr_philo <= 0)
		g->err_check = -2;
	else if (!g->params.time_to_die || g->params.time_to_die <= 0)
		g->err_check = -3;
	else if (!g->params.time_to_eat || g->params.time_to_eat <= 0)
		g->err_check = -4;
	else if (!g->params.time_to_sleep || g->params.time_to_sleep <= 0)
		g->err_check = -5;
	else if (g->params.must_eat && g->params.must_eat < 0)
	{
		if (argc == 5 && g->params.must_eat == -1)
			return ;
		g->err_check = -6;
	}
	return ;
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
	else
		g->params.must_eat = -1;
	ft_check_args_error(g, argc);
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

static int	ft_init_mutex_param(t_global *g)
{
	g->params.death = malloc(sizeof(pthread_mutex_t));
	g->params.write = malloc(sizeof(pthread_mutex_t));
	if (!g->params.death || !g->params.write)
	{
		g->err_check = -1;
		return (g->err_check);
	}
	if (pthread_mutex_init(g->params.death, NULL) != 0)
		g->err_check = -7;
	if (pthread_mutex_init(g->params.write, NULL) != 0)
		g->err_check = -7;
	return (g->err_check);
}

int	ft_init_struct(t_global *g, int argc, const char **argv)
{
	if (ft_parse_args(g, argc, argv) < 0)
		return (g->err_check);
	g->params.start_time = ft_get_time_in_ms(g);
	g->params.someone_died = malloc(sizeof(int));
	g->params.full_eaten = malloc(sizeof(int));
	if (!g->params.full_eaten)
	{
		g->err_check = -1;
		return (g->err_check);
	}
	if (ft_init_mutex_param(g) < 0)
		return (g->err_check);
	*g->params.full_eaten = 0;
	*g->params.someone_died = 0;
	printf("%d [%p]\n", *g->params.full_eaten, g->params.full_eaten);
	printf("%d [%p]\n", *g->params.someone_died, g->params.someone_died);
	if (ft_philo_init(g) < 0)
		return (g->err_check);
	if (ft_threads_init(g) < 0)
		return (g->err_check);
	ft_philo_checker(g);
	if (ft_threads_join(g) < 0)
		return (g->err_check);
	return (g->err_check);
}
