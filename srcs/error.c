/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabda <aabda@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 18:32:59 by aabda             #+#    #+#             */
/*   Updated: 2023/02/15 22:50:50 by aabda            ###   ########.fr       */
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
}

int	ft_error(t_global *g, int res)
{
	if (res < 0)
	{
		ft_putstr_fd(2, "\033[0;31;1mERROR !\033[0m\n");
		ft_error_message(res);
		if (g->philo)
			ft_free_philo(g);
	}
	return (res);
}

void	ft_free_philo(t_global *g)
{
	t_philo		*tmp;
	int			i;

	if (g->philo)
		tmp = g->philo;
	else
		tmp = NULL;
	i = -1;
	while (++i < g->params.nbr_philo)
	{
		if (!g->philo || !tmp)
			break ;
		g->philo = tmp;
		tmp = g->philo->next;
		if (g->philo->fork)
			free(g->philo->fork);
		free(g->philo);
		g->philo = NULL;
	}
}
