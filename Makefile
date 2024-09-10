# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dagarmil <dagarmil@student.42barcelon      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/28 12:48:53 by dagarmil          #+#    #+#              #
#    Updated: 2024/09/10 10:40:28 by dagarmil         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #
NAME = so_long.out

LIBFT_DIR = lib/Libft
MLX42_SRC = lib/MLX42
MLX42_BUILD = lib/MLX42/build

LIBFT_LIB = $(LIBFT_DIR)/Libftnew.a
MLX42_LIB = $(MLX42_BUILD)/libmlx42.a
MLX42_H   = lib/MLX42/include/MLX42/

CC = cc
CFLAGS = -Wall -Wextra -Werror
FLAGSMLX42 = -ldl -lglfw -pthread -lm
AR = ar rcs
SRC = src/so_long.c

all: $(NAME)

$(NAME): $(LIBFT_LIB) $(MLX42_LIB) $(SRC)
	$(CC) $(CFLAGS) -I./$(MLX42_H) $(SRC) $(LIBFT_LIB) $(MLX42_LIB) $(FLAGSMLX42) -o $(NAME)

$(LIBFT_LIB):
	@echo "Compiling Libft..."
	make -C $(LIBFT_DIR)
	@echo "Libft compiled"

clean:
	@echo "Cleaning..."
	make -C $(LIBFT_DIR) clean
	@echo "Cleaned"

fclean: clean
	@echo "Removing library..."
	rm -f $(NAME)
	rm -f $(LIBFT_LIB)
	@echo "Removed library"

re: fclean all
	@echo "Rebuilding everything..."

.PHONY: all clean fclean re

