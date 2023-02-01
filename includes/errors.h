/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabda <aabda@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 22:58:19 by aabda             #+#    #+#             */
/*   Updated: 2023/01/31 22:53:44 by aabda            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRORS_H
# define ERRORS_H

# define ERR_MALLOC "Memory allocation failure !\n"
# define ERR_NOT_ENOUGH_PHILO "You must have minimum one philosopher !\n"
# define ERR_INVALID_ARGS "Invalid number of argument(s), \
you must run the program as follows :\n\
\t./philo number_of_philosophers time_to_die time_to_eat time_to_sleep \
[number_of_times_each_philosopher_must_eat]\n"
# define ERR_NOT_ENOUGH_TIME_TO_DIE "The \"time to die\" (argv[2]) \
must not be 0 or less than 0 !\n"

#endif