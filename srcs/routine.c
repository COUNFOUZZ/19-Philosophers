/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabda <aabda@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 21:56:21 by aabda             #+#    #+#             */
/*   Updated: 2023/02/22 10:50:26 by aabda            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

static void	ft_sleep(t_params params, time_t time)
{
	time_t	now;
	time_t	start;

	start = ft_get_time_in_ms(NULL);
	while (!params.someone_died)
	{
		now = ft_get_time_in_ms(NULL);
		if (now - start >= time)
			break ;
		usleep(100);
	}
}

static void	ft_print_status(t_philo *philo, pthread_mutex_t *write, char *str)
{
	time_t	now;

	now = ft_get_time_in_ms(NULL) - philo->params.start_time;
	pthread_mutex_lock(write);
	if (!philo->params.someone_died && philo->eat_count != philo->params.must_eat)
		printf("[%ld ms] %d %s", now, philo->philo_id, str);
	pthread_mutex_unlock(write);
}

void	ft_simulation(t_philo *current)
{
	while (!current->params.someone_died && current->eat_count != current->params.must_eat)
	{
		pthread_mutex_lock(current->fork);
		ft_print_status(current, current->params.write, "has taken a fork\n");
		pthread_mutex_lock(current->next->fork);
		ft_print_status(current, current->params.write, "has taken a fork\n");
		ft_print_status(current, current->params.write, "is eating\n");
		ft_sleep(current->params, current->params.time_to_eat);
		current->eat_count++;
		if (current->eat_count == current->params.must_eat)
			printf("Philo_id #%d have finish to eat\n", current->philo_id);
			printf("[eat %d/%d]\n", current->eat_count, current->params.must_eat);
		pthread_mutex_unlock(current->fork);
		pthread_mutex_unlock(current->next->fork);
		ft_print_status(current, current->params.write, "is sleeping\n");
		ft_sleep(current->params, current->params.time_to_sleep);
		ft_print_status(current, current->params.write, "is thinking\n");
	}
}

void	ft_routine(t_philo *current)
{
	if (current->philo_id % 2)
		ft_sleep(current->params, 50);
	if (!current->params.someone_died)
		ft_simulation(current);
}
