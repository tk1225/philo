# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: takumasaokamoto <takumasaokamoto@studen    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/31 18:31:13 by takuokam          #+#    #+#              #
#    Updated: 2023/01/22 20:07:06 by takumasaoka      ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := philo
CCdfr		:= cc
CFLAGS	:= -Wall -Wextra -Werror 
# -fsanitize=thread
SRCS	:= philo_init.c print_timestamp.c mutex_handle.c time_utils.c philo_simu.c referee.c main.c libft_utils.c libft_utils2.c
OBJS	:= philo_init.o print_timestamp.o mutex_handle.o time_utils.o philo_simu.o referee.o main.o libft_utils.o libft_utils2.o

all: $(NAME)

$(NAME):$(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(SRCS)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY:	all clean fclean re
