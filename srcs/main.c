/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabda <aabda@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 13:47:09 by aabda             #+#    #+#             */
/*   Updated: 2023/02/01 15:28:52 by aabda            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

static int	ft_check_error(int res)
{
	if (res < 0)
	{
		ft_putstr_fd(2, "\033[0;31;1mERROR !\033[0m\n");
		if (res == -1)
			ft_putstr_fd(2, ERR_MALLOC);
		if (res == -2)
			ft_putstr_fd(2, ERR_NOT_ENOUGH_PHILO);
		if (res == -3)
			ft_putstr_fd(2, ERR_NOT_ENOUGH_TIME_TO_DIE);
		if (res == -4)
			ft_putstr_fd(2, ERR_NOT_ENOUGH_TIME_TO_EAT);
		if (res == -5)
			ft_putstr_fd(2, ERR_NOT_ENOUGH_TIME_TO_SLEEP);
		if (res == -6)
			ft_putstr_fd(2, ERR_NOT_ENOUGH_MUST_EAT);
	}
	return (res);
}

int	main(int argc, const char **argv)
{
	t_global	g;

	if (argc == 5 || argc == 6)
	{
		ft_check_error(ft_init_struct(&g, argv));
	}
	else
		ft_putstr_fd(2, ERR_INVALID_ARGS);
	return (-1);
}
