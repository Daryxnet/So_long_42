/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagarmil <dagarmil@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 15:35:06 by dagarmil          #+#    #+#             */
/*   Updated: 2024/09/19 15:39:53 by dagarmil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
#define SO_LONG_H

#include "MLX42.h"
#include "libft.h"
#include <stdlib.h>
#include <fcntl.h>

#define WIDTH 2000
#define HEIGHT 1000
#define TILE_SIZE 200

// Player struct
typedef struct s_player {
    int x;
    int y;
    mlx_image_t *current_image;  // Imagen actual del jugador
} t_player;

// Game struct
typedef struct s_game {
    t_player player;
    char **map;
    mlx_t *mlx;
    mlx_image_t *bg_image;
    mlx_image_t *wall_image;
    mlx_image_t *player_down_image;
    mlx_image_t *player_up_image;
    mlx_image_t *player_left_image;
    mlx_image_t *player_right_image;
    mlx_image_t *collect_image;
} t_game;

// Prototypes
void draw_tile(t_game *game, int x, int y);
void draw_map(t_game *game);
void move_player(t_game *game, int new_x, int new_y);
char **read_map(const char *filename);
void my_keyhook(mlx_key_data_t keydata, void* param);

#endif
