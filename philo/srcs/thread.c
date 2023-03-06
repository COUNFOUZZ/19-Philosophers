/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabda <aabda@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 21:33:40 by aabda             #+#    #+#             */
/*   Updated: 2023/02/18 21:56:17 by aabda            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	ft_threads_join(t_global *g)
{
	t_philo	*first;
	t_philo	*current;

	first = g->philo;
	current = g->philo;
	while (current)
	{
		if (pthread_join(current->thread_id, NULL) != 0)
		{
			g->err_check = -9;
			return (g->err_check);
		}
		current = current->next;
		if (current == first)
			break ;
	}
	return (0);
}

int	ft_threads_init(t_global *g)
{
	t_philo	*first;
	t_philo	*current;

	first = g->philo;
	current = g->philo;
	while (current)
	{
		if (pthread_create(&current->thread_id, \
			NULL, (void *)ft_routine, current) != 0)
		{
			g->err_check = -8;
			return (g->err_check);
		}
		current = current->next;
		if (current == first)
			break ;
	}
	return (0);
}
