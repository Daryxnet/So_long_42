/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyhook.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagarmil <dagarmil@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 11:28:50 by dagarmil          #+#    #+#             */
/*   Updated: 2024/09/17 11:31:25 by dagarmil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void move_player(t_game *game, int new_x, int new_y)
{
	char **map = game->map;
	if (map[new_y][new_x] != '1')
	{
		map[game->player.y][game->player.x] = '0';

		game->player.x = new_x;
		game->player.y = new_y;
		map[new_y][new_x] = 'P';
		ft_printf("player moved to (%d, %d)\n", new_x, new_y);
		draw_map(game->map, game->mlx, game->bg_texture, game->wall_texture, game->player_texture, game->collect_texture);
	}
	else
	{
		ft_printf("Wall at (%d, %d), can't move!\n", new_x, new_y);
	}
}

void my_keyhook(mlx_key_data_t keydata, void* param)
{
	t_game *game = (t_game *)param;

	if (keydata.action == MLX_PRESS)
	{
		if (keydata.key == MLX_KEY_ESCAPE)
			mlx_close_window(game->mlx);
		else if (keydata.key == MLX_KEY_W)
			move_player(game, game->player.x, game->player.y - 1);
		else if (keydata.key == MLX_KEY_S)
			move_player(game, game->player.x, game->player.y + 1);
		else if (keydata.key == MLX_KEY_A)
			move_player(game, game->player.x - 1, game->player.y);
		else if (keydata.key == MLX_KEY_D)
			move_player(game, game->player.x + 1, game->player.y);
	}
}
