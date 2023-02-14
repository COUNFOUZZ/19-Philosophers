/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabda <aabda@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 13:47:09 by aabda             #+#    #+#             */
/*   Updated: 2023/02/14 12:22:30 by aabda            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	main(int argc, const char **argv)
{
	t_global	g;

	if (argc == 5 || argc == 6)
	{
		ft_error(&g, ft_init_struct(&g, argc, argv));
		ft_free_philo(&g);
		printf("\n");
		ft_print_lst(&g);
	}
	else
		ft_putstr_fd(2, ERR_INVALID_ARGS);
	return (g.err_check);
}
