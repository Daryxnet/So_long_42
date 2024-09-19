/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagarmil <dagarmil@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 16:14:32 by dagarmil          #+#    #+#             */
/*   Updated: 2024/09/19 16:14:51 by dagarmil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

// Mover jugador
void move_player(t_game *game, int new_x, int new_y)
{
    char **map = game->map;

    if (map[new_y][new_x] != '1') {
        mlx_image_to_window(game->mlx, game->bg_image, game->player.x * TILE_SIZE, game->player.y * TILE_SIZE);

        if (map[game->player.y][game->player.x] == 'C')
            mlx_image_to_window(game->mlx, game->collect_image, game->player.x * TILE_SIZE, game->player.y * TILE_SIZE);

        map[game->player.y][game->player.x] = '0';
        game->player.x = new_x;
        game->player.y = new_y;
        map[new_y][new_x] = 'P';

        draw_tile(game, new_x, new_y);
        ft_printf("Player moved to (%d, %d)\n", new_x, new_y);
    } else {
        ft_printf("Wall at (%d, %d), can't move!\n", new_x, new_y);
    }
}

// Manejar teclas
void my_keyhook(mlx_key_data_t keydata, void* param)
{
    t_game *game = (t_game *)param;

    if (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT) {
        if (keydata.key == MLX_KEY_ESCAPE)
            mlx_close_window(game->mlx);
        else if (keydata.key == MLX_KEY_W) {
            game->player.current_image = game->player_up_image;
            move_player(game, game->player.x, game->player.y - 1);
        }
        else if (keydata.key == MLX_KEY_S) {
            game->player.current_image = game->player_down_image;
            move_player(game, game->player.x, game->player.y + 1);
        }
        else if (keydata.key == MLX_KEY_A) {
            game->player.current_image = game->player_left_image;
            move_player(game, game->player.x - 1, game->player.y);
        }
        else if (keydata.key == MLX_KEY_D) {
            game->player.current_image = game->player_right_image;
            move_player(game, game->player.x + 1, game->player.y);
        }
    }
}
