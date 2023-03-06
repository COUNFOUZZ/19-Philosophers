/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabda <aabda@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 13:47:09 by aabda             #+#    #+#             */
/*   Updated: 2023/03/06 14:03:43 by aabda            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

static void	ft_destroy_mutex(t_global *g)
{
	pthread_mutex_destroy(g->params.death);
	pthread_mutex_destroy(g->params.write);
}

int	main(int argc, const char **argv)
{
	t_global	g;

	if (argc == 5 || argc == 6)
	{
		if (ft_error(&g, ft_init_struct(&g, argc, argv)) < 0)
			return (g.err_check);
		ft_free_philo(&g);
		ft_destroy_mutex(&g);
		ft_free_struct(&g);
	}
	else
		ft_putstr_fd(2, ERR_INVALID_ARGS);
	return (g.err_check);
}
