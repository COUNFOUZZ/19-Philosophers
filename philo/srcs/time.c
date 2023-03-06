/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabda <aabda@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 15:16:10 by aabda             #+#    #+#             */
/*   Updated: 2023/03/07 00:13:50 by aabda            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

time_t	ft_get_time_in_ms(t_global *g)
{
	struct timeval	current_time;

	if (gettimeofday(&current_time, NULL) < 0)
	{
		g->err_check = -10;
		return (g->err_check);
	}
	return ((current_time.tv_sec * 1000) + (current_time.tv_usec / 1000));
}

void	ft_sleep(t_params params, time_t time)
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
