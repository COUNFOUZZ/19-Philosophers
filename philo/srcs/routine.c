/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabda <aabda@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 21:56:21 by aabda             #+#    #+#             */
/*   Updated: 2023/03/07 00:13:10 by aabda            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

static void	ft_print_status(t_philo *philo, pthread_mutex_t *write, char *str)
{
	time_t	now;

	now = ft_get_time_in_ms(NULL) - philo->params.start_time;
	pthread_mutex_lock(write);
	if (!(*philo->params.someone_died) && !(*philo->params.full_eaten))
		printf("%ld \033[0;34m%d\033[0;0m %s", now, philo->philo_id, str);
	pthread_mutex_unlock(write);
}

void	ft_simulation(t_philo *current)
{
	while (!(*current->params.someone_died) && !(*current->params.full_eaten))
	{
		pthread_mutex_lock(current->fork);
		ft_print_status(current, current->params.write, FORK);
		pthread_mutex_lock(current->next->fork);
		ft_print_status(current, current->params.write, FORK);
		ft_print_status(current, current->params.write, EAT);
		current->last_meal = \
			ft_get_time_in_ms(NULL) - current->params.start_time;
		current->eat_count++;
		ft_sleep(current->params, current->params.time_to_eat);
		pthread_mutex_unlock(current->fork);
		pthread_mutex_unlock(current->next->fork);
		ft_print_status(current, current->params.write, SLEEP);
		ft_sleep(current->params, current->params.time_to_sleep);
		ft_print_status(current, current->params.write, THINK);
	}
}

void	ft_routine(t_philo *current)
{
	time_t	now;

	if (current->params.nbr_philo == 1)
	{
		ft_sleep(current->params, current->params.time_to_die);
		now = ft_get_time_in_ms(NULL) - current->params.start_time;
		printf("%ld \033[0;34m%d\033[0;0m %s", now, current->philo_id, DIE);
		return ;
	}
	else
	{
		if (current->philo_id % 2)
			ft_sleep(current->params, 50);
		if (!(*current->params.someone_died))
			ft_simulation(current);
	}
}
