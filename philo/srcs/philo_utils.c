/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabda <aabda@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 23:58:20 by aabda             #+#    #+#             */
/*   Updated: 2023/03/07 00:14:52 by aabda            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

static void	ft_philo_die(t_global *g, time_t now)
{
	pthread_mutex_lock(g->params.death);
	pthread_mutex_lock(g->params.write);
	printf("%ld \033[0;34m%d\033[0;0m %s", now, g->philo->philo_id, DIE);
	*g->params.someone_died = 1;
	pthread_mutex_unlock(g->params.write);
	pthread_mutex_unlock(g->params.death);
}

static void	ft_check_must_eat(t_global *g)
{
	int	i;

	i = 0;
	while (i < g->params.nbr_philo)
	{
		if (g->philo->eat_count < g->params.must_eat)
			break ;
		i++;
		g->philo = g->philo->next;
	}
	if (i == g->params.nbr_philo)
		*g->params.full_eaten = 1;
}

void	ft_philo_checker(t_global *g)
{
	time_t	now;
	t_philo	*first;

	first = g->philo;
	while (!(*g->params.someone_died) && !(*g->params.full_eaten) \
	&& g->params.nbr_philo > 1)
	{
		usleep(100);
		while (g->philo)
		{
			now = ft_get_time_in_ms(g) - g->params.start_time;
			if (now >= g->philo->last_meal + g->params.time_to_die)
			{
				ft_philo_die(g, now);
				break ;
			}
			g->philo = g->philo->next;
			if (g->philo == first)
				break ;
		}
		if (g->params.must_eat != -1)
			ft_check_must_eat(g);
	}
}
