# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: takuokam <takuokam@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/31 18:31:13 by takuokam          #+#    #+#              #
#    Updated: 2023/01/14 16:16:44 by takuokam         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := philo
CCdfr		:= cc
CFLAGS	:= -Wall -Wextra -Werror 
#-fsanitize=thread
# void *referee(void *p)
SRCS	:= philo_init.c print_timestamp.c mutex_handle.c time_utils.c philo_simu.c referee.c main.c libft_utils.c
OBJS	:= philo_init.o print_timestamp.o mutex_handle.o time_utils.o philo_simu.o referee.o main.o libft_utils.o
# LIBFTDIR	:=	./libft
# LIBFT		:=	$(LIBFTDIR)/libft.a

all: $(NAME)

$(NAME):$(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(SRCS)
# $(LIBFT)
# $(MAKE) -C $(LIBFTDIR)

clean:
	rm -f $(OBJS)
# $(MAKE) clean -C $(LIBFTDIR)

fclean: clean
	rm -f $(NAME)
# $(MAKE) fclean -C $(LIBFTDIR)

re: fclean all

.PHONY:	all clean fclean re
