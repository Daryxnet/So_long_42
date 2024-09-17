/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagarmil <dagarmil@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 15:51:44 by dagarmil          #+#    #+#             */
/*   Updated: 2024/09/17 12:20:43 by dagarmil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "MLX42.h"
#include "libft.h"
#define WIDTH 1500
#define HEIGHT 1400

//Player struct
typedef struct s_player {
	int x;
	int y;
} t_player;

//Map Struct
typedef struct s_game {
	t_player player;
	char **map;
	mlx_t *mlx;
	mlx_texture_t *bg_texture;
	mlx_texture_t *wall_texture;
	mlx_texture_t *player_texture;
	mlx_texture_t *collect_texture;
} t_game;


void draw_map(char **map, mlx_t* mlx,mlx_texture_t* bg_texture, mlx_texture_t* wall_texture, mlx_texture_t* player_texture, mlx_texture_t* collect_texture);

// Move Player
void move_player(t_game *game, int new_x, int new_y)
{
	char **map = game->map;
	if (map[new_y][new_x] != '1') //if it's not a wall
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

// Operate the keys
void my_keyhook(mlx_key_data_t keydata, void* param)
{
	t_game *game = (t_game *)param;

	if (keydata.action == MLX_PRESS)
	{
		if (keydata.key == MLX_KEY_ESCAPE)
			mlx_close_window(game->mlx);
		// If we PRESS the 'W' key, move "UP".
		else if (keydata.key == MLX_KEY_W)
			move_player(game, game->player.x, game->player.y - 1);

		// If we PRESS the 'S' key, move "Down".
		if (keydata.key == MLX_KEY_S)
			move_player(game, game->player.x, game->player.y + 1);

		// If we PRESS the 'A' key, move "Left".
		if (keydata.key == MLX_KEY_A)
			move_player(game, game->player.x - 1, game->player.y);

		// If we PRESS the 'D' key, move "Right".
		if (keydata.key == MLX_KEY_D)
			move_player(game, game->player.x + 1, game->player.y);
	}
}

void	draw_map(char **map, mlx_t* mlx, mlx_texture_t* bg_texture, mlx_texture_t* wall_texture, mlx_texture_t* player_texture, mlx_texture_t* collect_texture)
{
	int	title_size = 200;
	int	y = 0;

	while (map[y])
	{
		int	x = 0;
		while (map[y][x])
		{
			mlx_image_t* bg = mlx_texture_to_image(mlx, bg_texture);
			if (bg)
				mlx_image_to_window(mlx, bg, x * title_size, y * title_size);

			if (map[y][x] == '1')
			{
				mlx_image_t* wall = mlx_texture_to_image(mlx, wall_texture);
				if (wall)
					mlx_image_to_window(mlx, wall, x * title_size, y * title_size);
			}
			if (map [y][x] == 'P')
			{
				mlx_image_t* player = mlx_texture_to_image(mlx, player_texture);
				if (player)
					mlx_image_to_window(mlx, player, x * title_size, y * title_size);
			}
			if (map [y][x] == 'C')
			{
				mlx_image_t* collect = mlx_texture_to_image(mlx, collect_texture);
				if (collect)
					mlx_image_to_window(mlx, collect, x * title_size, y * title_size);
			}
			x++;
		}
		y++;
	}
}

char	**read_map(const char *filename)
{
	int	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		ft_printf("%s", "Error reading map\n");
		return (NULL);
	}

	char	*line;
	char	**map = malloc(sizeof(char*) * 100);
	int	i = 0;
	while ((line = get_next_line(fd)) != NULL)
	{
		map[i++] = line;
	}
	map[i] = NULL;
	close(fd);
	return (map);
}

int32_t	main(void)
{
	mlx_t*	mlx;

	if (!(mlx = mlx_init(WIDTH, HEIGHT, "Window w B", false)))
		return (EXIT_FAILURE);

	mlx_texture_t* bg_texture = mlx_load_png("bg.png");
	mlx_texture_t* wall_texture = mlx_load_png("wall_jung.png");
	mlx_texture_t* player_texture = mlx_load_png("player.png");
	mlx_texture_t* collect_texture = mlx_load_png("Gold.png");
	if (!bg_texture || !wall_texture || !player_texture || !collect_texture)
	{
		ft_printf("%s", "Error loading textures\n");
		mlx_terminate(mlx);
		return EXIT_FAILURE;
	}

	char	**map = read_map("map.ber");
	if (!map)
	{
		mlx_delete_texture(wall_texture);
		mlx_delete_texture(bg_texture);
		mlx_delete_texture(player_texture);
		mlx_delete_texture(collect_texture);
		mlx_terminate(mlx);
		return EXIT_FAILURE;
	}

	t_game game;
	game.map = map;
	game.mlx = mlx;
	game.bg_texture = bg_texture;
	game.wall_texture = wall_texture;
	game.player_texture = player_texture;
	game.collect_texture = collect_texture;

	for (int y = 0; map[y]; y++)
	{
		for (int x =  0; map[y][x]; x++)
		{
			if (map[y][x] == 'P')
			{
				game.player.x = x;
				game.player.y = y;
			}
		}
	}
	//ft_printf("%s", *map);
	draw_map(map, mlx, bg_texture, wall_texture, player_texture, collect_texture);

	mlx_key_hook(mlx, my_keyhook, &game);
	mlx_loop(mlx);

	for (int i = 0; map[i]; i++)
		free(map[i]);
	free(map);
	mlx_delete_texture(bg_texture);
	mlx_delete_texture(wall_texture);
	mlx_delete_texture(player_texture);
	mlx_delete_texture(collect_texture);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}

