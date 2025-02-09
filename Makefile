# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: girindi <girindi@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: Invalid date        by                   #+#    #+#              #
#    Updated: 2025/02/05 15:48:40 by girindi          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
NAME = cub3D
FLAGS = -Wall -Wextra -Werror -g
SRC =	src/main.c src/debug.c \
		src/parsing/parsing.c src/parsing/parsing2.c src/parsing/parsing3.c src/parsing/parsing_utils.c \
		src/parsing/parsing_utils2.c src/parsing/parsing_utils3.c\
		src/parsing/parsing_walls.c src/parsing/parsing_walls2.c src/parsing/parsing_walls3.c \
		src/utils/utils.c src/utils/utils2.c src/utils/utils3.c src/utils/gnl.c \
		src/init/init.c src/init/init2.c \
		src/controls/controls.c src/controls/control_helpers.c src/controls/collisions.c src/controls/check_dir_left.c src/controls/check_dir_right.c \
		src/rendering/rendering.c src/rendering/rendering_utils.c src/rendering/rendering_utils2.c \
		src/rendering/rendering_utils3.c src/rendering/rendering_utils4.c \
		src/free.c
OBJ = $(SRC:.c=.o)
LIB = mlx_linux/libmlx_Linux.a -lXext -lm
MLX = mlx_linux
LIB = libft.a

all: $(NAME)

$(NAME): $(SRC)
		@echo "\033[32mCompiling $(NAME) 🚀"
		@cd libft/ && $(MAKE) && mv $(LIB) ../
		@$(MAKE) -C $(MLX)
		$(CC) $(FLAGS) $(SRC) $(LIB) -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz -o $(NAME)
		@echo "$(GREEN)$(NAME) compilata con successo❗️ 📁$(DEFAULT)"

clean:
		rm -f $(OBJ)
		@cd libft && $(MAKE) clean
		@cd $(MLX) && $(MAKE) clean
		@echo "$(CIANO)file oggetto di $(NAME) rimossi con successo❗️ 🪦$(DEFAULT)"

fclean: clean
		rm -f $(LIB)
		rm -f $(NAME)
		cd libft && make fclean
		@echo "$(CIANO)directory OBJ rimossa...$(DEFAULT)"
		@echo "$(RED)$(NAME) rimossa con successo❗️ ❌$(DEFAULT)"

re: fclean  all