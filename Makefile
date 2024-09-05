# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dagarmil <dagarmil@student.42barcelon      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/28 12:48:53 by dagarmil          #+#    #+#              #
#    Updated: 2024/08/30 19:06:11 by dagarmil         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME     = so_long
CFLAGS   = -Wextra -Werror -Wall
LIBMLX   = ./lib/MLX42/include/MLX42
MLXFLAGS = -L/usr/lib/x86_64-linux-gnu -lglfw -lGL -lm -pthread

comp: 
	cc $(CFLAGS) -I$(LIBMLX) test_hook_key.c libmlx42.a $(MLXFLAGS)

.PHONY: comp
