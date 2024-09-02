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

NAME   = so_long
CFLAGS = -Wextra -Werror -Wall -Ldl -lglfw -pthread -lm
LIBMLX = ./lib/MLX42/include/MLX42

comp: 
	cc $(CFLAGS) -I$(LIBMLX) test_hook_key.c libmlx42.a

.PHONY: comp
