# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bmoiroud <bmoiroud@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/11/09 18:43:48 by bmoiroud          #+#    #+#              #
#    Updated: 2018/03/11 17:37:14 by bmoiroud         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SRCS =	ft_strlen.c	    ft_strdup.c      ft_strcpy.c    ft_strncpy.c    \
		ft_strcat.c     ft_strncat.c     ft_strlcat.c   ft_strchr.c     \
		ft_strrchr.c    ft_strstr.c      ft_strnstr.c   ft_strcmp.c     \
		ft_strncmp.c    ft_strnew.c      ft_strdel.c    ft_strclr.c     \
		ft_striter.c    ft_striteri.c    ft_strmap.c    ft_strmapi.c    \
		ft_strequ.c     ft_strnequ.c     ft_strsub.c    ft_strjoin.c    \
		ft_strtrim.c    ft_strsplit.c	 ft_strjoinc.c  ft_strnjoin.c	\
		\
		ft_memset.c     ft_memcpy.c      ft_memccpy.c   ft_memmove.c    \
		ft_memchr.c     ft_memcmp.c      ft_memalloc.c  ft_memdel.c     \
		\
		ft_bzero.c      ft_isalpha.c     ft_isdigit.c   ft_isalnum.c    \
		ft_isascii.c    ft_isprint.c     ft_toupper.c   ft_tolower.c    \
		\
		ft_putchar.c    ft_putchar_fd.c  ft_putstr.c    ft_putstr_fd.c  \
		ft_putnbr.c     ft_putnbr_fd.c   ft_putendl.c   ft_putendl_fd.c \
		\
		ft_atoi.c       ft_itoa.c        ft_atoi_base.c	ft_itoa_base.c	\
		ft_pow.c		ft_fpow.c		 ft_atod.c		ft_dtoa.c		\
		\
		ft_lstadd.c     ft_lstdel.c	     ft_lstdelone.c ft_lstiter.c	\
		ft_lstiter.c    ft_lstnew.c	     ft_lstmap.c					\
		\
		ft_swap.c       ft_nblen.c		 ft_countwords.c ft_getword.c	\
		ft_strrev.c														\
		\
		get_next_line.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME):
	@gcc -Wall -Wextra -Werror -c $(SRCS)
	@echo "\033[0;32m[✓] Built C object"
	@ar rc $(NAME) $(OBJS)
	@ranlib $(NAME)
	@echo "\033[0;31m[✓] Library done" $(NAME)

clean:
	@rm -rf $(OBJS)
	@echo "\033[0;33m[✓] Removed library object files"

fclean: clean
	@rm -rf $(NAME)
	@echo "\033[0;33m[✓] Removed" $(NAME)

re: fclean all

.PHONY: all, clean, fclean, re
