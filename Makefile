# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: takuokam <takuokam@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/31 18:31:13 by takuokam          #+#    #+#              #
#    Updated: 2022/12/14 17:14:29 by takuokam         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := philo
CC		:= cc
CFLAGS	:= -Wall -Wextra -Werror 
SRCS	:= philo_init.c
OBJS	:= philo_init.o
LIBFTDIR	:=	./libft
LIBFT		:=	$(LIBFTDIR)/libft.a


all: $(NAME)

$(NAME):$(OBJS)
	$(MAKE) -C $(LIBFTDIR)
	$(CC) $(CFLAGS) -o $(NAME) $(SRCS) $(LIBFT)

clean:
	rm -f $(OBJS)
	$(MAKE) clean -C $(LIBFTDIR)

fclean: clean
	rm -f $(NAME)
	$(MAKE) fclean -C $(LIBFTDIR)

re: fclean all

.PHONY:	all clean fclean re
