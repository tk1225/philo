# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: takumasaokamoto <takumasaokamoto@studen    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/31 18:31:13 by takuokam          #+#    #+#              #
#    Updated: 2022/12/29 17:57:10 by takumasaoka      ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := philo
CCdfr		:= cc
CFLAGS	:= -Wall -Wextra -Werror -fsanitize=thread
SRCS	:= philo_init.c print_timestamp.c
OBJS	:= philo_init.o print_timestamp.o
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
