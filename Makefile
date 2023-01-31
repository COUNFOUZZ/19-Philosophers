# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aabda <aabda@student.s19.be>               +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/30 13:36:56 by aabda             #+#    #+#              #
#    Updated: 2023/01/31 01:35:28 by aabda            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= philo
DIR		= srcs/
CC		= gcc
FLAGS	= -pthread -Wall -Wextra

SRCS = $(DIR)main.c $(DIR)libft_utils.c \
	$(DIR)utils.c $(DIR)add_philo.c

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