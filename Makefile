# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bmoiroud <bmoiroud@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/02/18 18:32:53 by bmoiroud          #+#    #+#              #
#    Updated: 2018/03/17 11:56:05 by eferrand         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = rt

SRCDIR = srcs/c

SRC_NAME = 	border.c \
		   	button.c \
		   	button2.c \
			cl.c \
		   	client.c \
		   	ft_check.c \
		   	ft_errors.c \
			ft_filters.c \
			ft_filters2.c \
		   	ft_get_data.c \
			ft_get_data2.c \
			ft_get_data3.c \
			ft_get_data4.c \
		   	ft_get_objects.c \
		   	ft_get_objects2.c \
			ft_get_scene.c \
		   	ft_help.c \
		   	ft_info.c \
		   	ft_info2.c \
		   	ft_info3.c \
		   	ft_init.c \
		   	ft_menus.c \
		   	ft_move.c \
		   	ft_mysdl.c \
		   	ft_parse_conf.c \
		   	ft_parse.c \
		   	ft_vector.c \
		   	ft_vector2.c \
		   	loading.c \
		   	main.c \
		   	mouse.c \
		   	picture.c \
		   	sdl_event.c \
		   	sdl.c \
		   	serialize.c \
		   	serialize2.c \
		   	serialize3.c \
		   	server.c \
		   	unserialize.c \
		   	unserialize2.c \
		   	unserialize3.c

SRC = $(addprefix $(SRCDIR)/, $(SRC_NAME))

OBJDIR = objs

OBJ = $(addprefix $(OBJDIR)/, $(SRC_NAME:.c=.o))

CFLAGS = -Wall -Werror -Wextra

SDL = -I Frameworks/SDL2.framework/Headers/\
	  -I Frameworks/SDL2_ttf.framework/Headers/\
	  -I Frameworks/SDL2_image.framework/Headers/\

LIB = -Llibft/ -lft

INCLUDES = -I./includes/ -I./libft/ $(SDL)

FRAMEWORKS = -framework OpenCL -rpath @loader_path/Frameworks \
			 -framework SDL2 -framework SDL2_ttf -framework SDL2_image -F ./Frameworks

all:$(NAME)

$(NAME): $(OBJ)
	@make -C libft/
	@echo "\033[0;34m--------------------------------"
	@gcc $(CFLAGS) $(OBJ) $(INCLUDES) $(LIB) $(FRAMEWORKS) -o $@
	@echo "\033[0;31m[✓] Linked C executable" $(NAME)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@/bin/mkdir -p $(OBJDIR)
	@gcc $(CFLAGS) -c $< -o $@ $(INCLUDES)
	@echo "\033[0;32m[✓] Built C object" $@

clean:
	@make -C libft/ clean
	@/bin/rm -Rf $(OBJDIR)
	@echo "\033[0;33m[✓] Removed object directory" $(OBJDIR)

fclean: clean
	@make -C libft/ fclean
	@/bin/rm -f $(NAME)
	@echo "\033[0;33m[✓] Removed executable" $(NAME)

re: fclean all

.PHONY: all clean fclean re
