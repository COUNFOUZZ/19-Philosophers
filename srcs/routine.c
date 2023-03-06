/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabda <aabda@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 21:56:21 by aabda             #+#    #+#             */
/*   Updated: 2023/03/06 16:11:29 by aabda            ###   ########.fr       */
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

static void	ft_check_must_eat(t_global *g)
{
	int	i;

	i = 0;
	while (i < g->params.nbr_philo)
	{
		if (g->philo->eat_count < g->params.must_eat)
			break ;
		i++;
	}
	if (i == g->params.nbr_philo)
		*g->params.full_eaten = 1;

}

void	ft_philo_checker(t_global *g)
{
	time_t	now;
	t_philo	*first;

	first = g->philo;
	while (!(*g->params.someone_died) && !(*g->params.full_eaten))
	{
		usleep(100);
		while (g->philo)
		{
			now = ft_get_time_in_ms(g) - g->params.start_time;
			if (now >= g->philo->last_meal + g->params.time_to_die)
			{
				pthread_mutex_lock(g->params.death);
				pthread_mutex_lock(g->params.write);
				printf("%ld \033[0;34m%d\033[0;0m %s", now, g->philo->philo_id, "\033[0;31mdied\033[0;0m\n");
				*g->params.someone_died = 1;
				pthread_mutex_unlock(g->params.write);
				pthread_mutex_unlock(g->params.death);
				break ;
			}
			g->philo = g->philo->next;
			if (g->philo == first)
				break ;
		}
		if (g->params.must_eat != -1 && g->params.nbr_philo > 1)
			ft_check_must_eat(g);
	}
}

void	ft_simulation(t_philo *current)
{
	while (!(*current->params.someone_died) && !(*current->params.full_eaten))
	{
		if (current->params.nbr_philo == 1)
			continue ;
		pthread_mutex_lock(current->fork);
		ft_print_status(current, current->params.write, "\033[0;33mhas taken a fork\033[0;0m\n");
		pthread_mutex_lock(current->next->fork);
		ft_print_status(current, current->params.write, "\033[0;33mhas taken a fork\033[0;0m\n");
		ft_print_status(current, current->params.write, "\033[0;32mis eating\033[0;0m\n");
		current->last_meal = ft_get_time_in_ms(NULL) - current->params.start_time;
		current->eat_count++;
		ft_sleep(current->params, current->params.time_to_eat);
		pthread_mutex_unlock(current->fork);
		pthread_mutex_unlock(current->next->fork);
		// if (current->eat_count == current->params.must_eat)
		// {
		// 	(*current->params.full_eaten)++;
		// 	break ;
		// }
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
