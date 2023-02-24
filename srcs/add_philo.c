/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_philo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabda <aabda@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 01:31:55 by aabda             #+#    #+#             */
/*   Updated: 2023/02/23 01:00:59 by aabda            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	ft_add_prev_for_first_and_last(t_global *g)
{
	t_philo	*first;
	t_philo	*b_last;
	t_philo	*tmp;

	if (g->params.nbr_philo > 1)
	{
		first = g->philo;
		tmp = g->philo;
		while (tmp)
		{
			if (tmp->next->next == first)
				b_last = tmp;
			if (tmp->next == first)
				break ;
			tmp = tmp->next;
		}
		if (tmp)
			tmp->prev = b_last;
		first->prev = tmp;
	}
}

static int	ft_add_value_to_philo(t_global *g, t_philo *new, int philo_nbr)
{
	new->philo_id = philo_nbr + 1;
	new->fork = malloc(sizeof(pthread_mutex_t));
	if (!new->fork)
	{
		g->err_check = -1;
		return (g->err_check);
	}
	if (pthread_mutex_init(new->fork, NULL) != 0)
		g->err_check = -7;
	new->last_meal = ft_get_time_in_ms(g);
	new->eat_count = 0;
	new->params = g->params;
	new->next = NULL;
	return (g->err_check);
}

static void	ft_add_philo2(t_global *g, t_philo *c, t_philo *n_p, int philo_nbr)
{
	c = g->philo;
	while (c->next)
	{
		c->next->prev = c;
		c = c->next;
	}
	c->next = n_p;
	if (philo_nbr == g->params.nbr_philo - 1)
	{
		c = c->next;
		c->next = g->philo;
	}
}

int	ft_add_philo(t_global *g, int philo_nbr)
{
	t_philo	*current;
	t_philo	*new_philo;

	current = NULL;
	new_philo = malloc(sizeof(t_philo));
	if (!new_philo)
	{
		g->err_check = -1;
		return (g->err_check);
	}
	if (ft_add_value_to_philo(g, new_philo, philo_nbr) != 0)
		return (g->err_check);
	if (!g->philo)
	{
		new_philo->prev = NULL;
		g->philo = new_philo;
	}
	else
	{
		ft_add_philo2(g, current, new_philo, philo_nbr);
	}
	return (g->err_check);
}

void	ft_print_lst(t_global *g)
{
	int		i;
	t_philo	*current;

	i = -1;
	current = g->philo;
	while (++i < g->params.nbr_philo)
	{
		printf("[%p]<- [%p | Philo_id.%d] ->[%p]\n", current->prev, current, current->philo_id, current->next);
		current = current->next;
	}
}
