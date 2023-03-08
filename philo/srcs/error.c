/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabda <aabda@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 18:32:59 by aabda             #+#    #+#             */
/*   Updated: 2023/03/08 17:12:35 by aabda            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

static void	ft_error_message(int res)
{
	if (res == -1)
		ft_putstr_fd(2, ERR_MALLOC);
	else if (res == -2)
		ft_putstr_fd(2, ERR_NOT_ENOUGH_PHILO);
	else if (res == -3)
		ft_putstr_fd(2, ERR_NOT_ENOUGH_TIME_TO_DIE);
	else if (res == -4)
		ft_putstr_fd(2, ERR_NOT_ENOUGH_TIME_TO_EAT);
	else if (res == -5)
		ft_putstr_fd(2, ERR_NOT_ENOUGH_TIME_TO_SLEEP);
	else if (res == -6)
		ft_putstr_fd(2, ERR_NOT_ENOUGH_MUST_EAT);
	else if (res == -7)
		ft_putstr_fd(2, ERR_MUTEX_INIT);
	else if (res == -8)
		ft_putstr_fd(2, ERR_THREAD_INIT);
	else if (res == -9)
		ft_putstr_fd(2, ERR_THREAD_JOIN);
	else if (res == -10)
		ft_putstr_fd(2, ERR_GET_TIME);
}

void	ft_free_struct(t_global *g)
{
	if (g->params.someone_died)
		free(g->params.someone_died);
	if (g->params.full_eaten)
		free(g->params.full_eaten);
	if (g->params.death)
		free(g->params.death);
	if (g->params.write)
		free(g->params.write);
}

int	ft_error(t_global *g, int res)
{
	if (res < 0)
	{
		ft_putstr_fd(2, "\033[0;31;1mERROR !\033[0m\n");
		ft_error_message(res);
		if (g->philo)
			ft_free_philo(g);
		ft_free_struct(g);
	}
	return (res);
}

void	ft_free_philo(t_global *g)
{
	t_philo	*first;
	t_philo	*current;
	t_philo	*tmp;

	if (!g->philo)
		return ;
	first = g->philo;
	current = g->philo;
	tmp = g->philo;
	while (current)
	{
		tmp = current;
		current = current->next;
		if (tmp->fork)
		{
			pthread_mutex_destroy(tmp->fork);
			free(tmp->fork);
		}
		free(tmp);
		tmp = NULL;
		if (current == first)
			return ;
	}
}
