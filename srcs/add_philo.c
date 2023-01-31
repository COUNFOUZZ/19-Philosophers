/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_philo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabda <aabda@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 01:31:55 by aabda             #+#    #+#             */
/*   Updated: 2023/01/31 20:18:14 by aabda            ###   ########.fr       */
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
		tmp->prev = b_last;
		first->prev = tmp;
	}
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

void	ft_add_philo(t_global *g, int philo_nbr)
{
	t_philo	*new_philo;
	t_philo	*current;
	new_philo = malloc(sizeof(t_philo));
	current = NULL;
	if (!new_philo)
	{
		g->err_check = -1;
		return ;
	}
	new_philo->philo_number = philo_nbr + 1;
	new_philo->next = NULL;
	if (!g->philo)
	{
		new_philo->prev = NULL;
		g->philo = new_philo;
	}
	else
	{
		ft_add_philo2(g, current, new_philo, philo_nbr);
	}
}

void	ft_print_lst(t_global *g)
{
	int		i;
	t_philo	*current;

	i = -1;
	current = g->philo;
	while (++i < g->params.nbr_philo)
	{
		printf("[%p]\tPhilo.%d\tprev = %p\tnext = %p\n", current, current->philo_number, current->prev, current->next);
		current = current->next;
	}
}
