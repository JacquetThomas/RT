# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bmoiroud <bmoiroud@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/11/09 18:43:48 by bmoiroud          #+#    #+#              #
#    Updated: 2017/02/17 16:50:55 by bmoiroud         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a

SRCS =	ft_printf.c    ft_itoa_base.c    ft_char.c		 ft_decimal.c	\
		ft_flags.c     ft_flags2.c       ft_printnbr.c	 ft_atoi_base.c	\
		ft_other.c	   ft_nbrflags.c	 ft_putwchar.c	 ft_tools.c		\
		ft_convert.c   ft_strings.c

OBJS =	ft_printf.o    ft_itoa_base.o    ft_char.o		 ft_decimal.o	\
		ft_flags.o     ft_flags2.o       ft_printnbr.o	 ft_atoi_base.o	\
		ft_other.o	   ft_nbrflags.o	 ft_putwchar.o	 ft_tools.o		\
		ft_convert.o   ft_strings.o

all: $(NAME)

$(NAME):
	make -C libft/
	gcc -Wall -Wextra -Werror -c -g $(SRCS)
	cp ./libft/libft.a ./$(NAME)
	ar rc $(NAME) $(OBJS)
	ranlib $(NAME)

clean:
	make -C libft/ clean
	rm -rf $(OBJS)

fclean: clean
	make -C libft/ fclean
	rm -rf $(NAME)

re: fclean all

.PHONY: all, clean, fclean, re
