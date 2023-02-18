# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aabda <aabda@student.s19.be>               +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/30 13:36:56 by aabda             #+#    #+#              #
#    Updated: 2023/02/18 21:57:38 by aabda            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= philo
DIR		= srcs/
CC		= gcc
FLAGS	= -pthread -Wall -Wextra -Werror

SRCS = $(DIR)main.c $(DIR)libft_utils.c \
	$(DIR)utils.c $(DIR)add_philo.c \
	$(DIR)error.c $(DIR)thread.c \
	$(DIR)routine.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

%.o: %.c
	$(CC) $(FLAGS) -o $@ -c $<

$(NAME): $(OBJS)
	$(CC) $(FLAGS) -o $(NAME) $(OBJS)

norm:
	norminette -R CheckDefine

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY:	all clean fclean re norm