/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagarmil <dagarmil@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 16:15:10 by dagarmil          #+#    #+#             */
/*   Updated: 2024/09/19 16:15:41 by dagarmil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

// Dibujar un tile específico
void draw_tile(t_game *game, int x, int y)
{
    mlx_image_to_window(game->mlx, game->bg_image, x * TILE_SIZE, y * TILE_SIZE);

    if (game->map[y][x] == '1')
        mlx_image_to_window(game->mlx, game->wall_image, x * TILE_SIZE, y * TILE_SIZE);
    else if (game->map[y][x] == 'P')
        mlx_image_to_window(game->mlx, game->player.current_image, x * TILE_SIZE, y * TILE_SIZE);
    else if (game->map[y][x] == 'C')
        mlx_image_to_window(game->mlx, game->collect_image, x * TILE_SIZE, y * TILE_SIZE);
}

// Dibujar el mapa completo
void draw_map(t_game *game)
{
    int y = 0;
    while (game->map[y]) {
        int x = 0;
        while (game->map[y][x]) {
            draw_tile(game, x, y);
            x++;
        }
        y++;
    }
}
