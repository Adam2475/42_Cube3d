# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: adapassa <adapassa@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/25 10:45:45 by adapassa          #+#    #+#              #
#    Updated: 2024/11/25 11:37:23 by adapassa         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
NAME = cube3d
FLAGS =  -Wall -Wextra -Werror -g
SRC = src/main.c src/init.c \

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