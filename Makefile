# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: takuokam <takuokam@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/31 18:31:13 by takuokam          #+#    #+#              #
#    Updated: 2022/12/14 15:19:50 by takuokam         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := philo
CC		:= cc
CFLAGS	:= -Wall -Wextra -Werror 
SRCS	:= print_timestamp.c
OBJS	:= print_timestamp.o
LIBFTDIR	:=	./libft
LIBFT		:=	$(LIBFTDIR)/libft.a


all: $(NAME)

$(NAME):$(OBJS)
	$(MAKE) -C $(LIBFTDIR)
	$(MAKE) -C $(PRINTFDIR)
	$(CC) $(CFLAGS) -o $(NAME) $(SRCS) $(LIBFT)

clean:
	rm -f $(OBJS)
	$(MAKE) clean -C $(LIBFTDIR)

fclean: clean
	rm -f $(NAME)
	$(MAKE) fclean -C $(LIBFTDIR)

re: fclean all

.PHONY:	all clean fclean re
