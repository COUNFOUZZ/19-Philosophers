/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabda <aabda@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 21:56:21 by aabda             #+#    #+#             */
/*   Updated: 2023/02/24 16:41:34 by aabda            ###   ########.fr       */
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

void	ft_philo_checker(t_global *g)
{
	time_t	now;

	while (!(*g->params.someone_died) && *g->params.full_eaten != g->params.nbr_philo)
	{
		usleep(100);
		while (g->philo && *g->params.full_eaten != g->params.nbr_philo)
		{
			now = ft_get_time_in_ms(g) - g->params.start_time;
			if (now >= g->philo->last_meal + g->params.time_to_die)
			{
				pthread_mutex_lock(g->params.death);
				pthread_mutex_lock(g->params.write);
				// printf("%ld\n", now);
				// printf("[%ld]\n", ft_get_time_in_ms(NULL) - (g->philo->last_meal + g->params.time_to_die));
				printf("%ld %d %s", now, g->philo->philo_id, "died\n");
				*g->params.someone_died = 1;
				pthread_mutex_unlock(g->params.write);
				pthread_mutex_unlock(g->params.death);
				break ;
			}
			g->philo = g->philo->next;
		}
	}
}

static void	ft_sleep(t_params params, time_t time)
{
	time_t	now;
	time_t	start;

	start = ft_get_time_in_ms(NULL);
	while (!(*params.someone_died))
	{
		now = ft_get_time_in_ms(NULL);
		if (now - start >= time)
			break ;
		usleep(100);
	}
}


void	ft_simulation(t_philo *current)
{
	//	1 philo = segfault
	while (!(*current->params.someone_died) && *current->params.full_eaten != current->params.nbr_philo)
	{
		pthread_mutex_lock(current->fork);
		ft_print_status(current, current->params.write, "\033[0;33mhas taken a fork\033[0;0m\n");
		pthread_mutex_lock(current->next->fork);
		ft_print_status(current, current->params.write, "\033[0;33mhas taken a fork\033[0;0m\n");
		ft_print_status(current, current->params.write, "\033[0;32mis eating\033[0;0m\n");
		current->last_meal = ft_get_time_in_ms(NULL);
		current->eat_count++;
		ft_sleep(current->params, current->params.time_to_eat);
		pthread_mutex_unlock(current->fork);
		pthread_mutex_unlock(current->next->fork);
		if (current->eat_count == current->params.must_eat)
		{
			pthread_mutex_lock(current->params.eat);
			(*current->params.full_eaten)++;
			pthread_mutex_unlock(current->params.eat);
			printf("philo #%d [%d]\n", current->philo_id, *current->params.full_eaten);
			break ;
		}
		ft_print_status(current, current->params.write, "\033[0;35mis sleeping\033[0;0m\n");
		ft_sleep(current->params, current->params.time_to_sleep);
		ft_print_status(current, current->params.write, "\033[0;36mis thinking\033[0;0m\n");
	}
}

void	ft_routine(t_philo *current)
{
	if (current->philo_id % 2)
		ft_sleep(current->params, 50);
	if (!(*current->params.someone_died))
		ft_simulation(current);
}
