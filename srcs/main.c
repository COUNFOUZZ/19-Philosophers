/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabda <aabda@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 13:47:09 by aabda             #+#    #+#             */
/*   Updated: 2023/01/30 23:05:27 by aabda            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	main(int argc, const char **argv)
{
	t_global	g;

	if (argc == 5 || argc == 6)
	{
		ft_init_struct(&g, argv);
		return (0);
	}
	else
		printf("Invalide number of argument\n");
}
