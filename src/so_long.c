/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagarmil <dagarmil@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 15:52:18 by dagarmil          #+#    #+#             */
/*   Updated: 2024/09/13 17:18:24 by dagarmil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "MLX42.h"
#include "libft.h"
#define WIDTH 1500
#define HEIGHT 1400

void my_keyhook(mlx_key_data_t keydata, void* param)
{
	// If we PRESS the 'ESCAPE' key, close Window.
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		mlx_close_window((mlx_t*)param);

	// If we PRESS the 'W' key, print "UP".
	if (keydata.key == MLX_KEY_W && keydata.action == MLX_PRESS)
		ft_printf("UP\n");

	// If we PRESS the 'S' key, print "Down".
	if (keydata.key == MLX_KEY_S && keydata.action == MLX_PRESS)
		ft_printf("Down\n");

	// If we PRESS the 'A' key, print "Left".
	if (keydata.key == MLX_KEY_A && keydata.action == MLX_PRESS)
		ft_printf("Left\n");

	// If we PRESS the 'D' key, print "Right".
	if (keydata.key == MLX_KEY_D && keydata.action == MLX_PRESS)
		ft_printf("Right\n");
}

void	draw_map(char **map, mlx_t* mlx, mlx_texture_t* wall_texture, mlx_texture_t* player_texture)
{
	int	title_size = 164;
	int	y = 0;

	while (map[y])
	{
		int	x = 0;
		while (map[y][x])
		{
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
		ft_printf("%s", "Error read map");
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

	mlx_texture_t* wall_texture = mlx_load_png("wall_jung2.png");
	mlx_texture_t* player_texture = mlx_load_png("player.png");
	if (!wall_texture || !player_texture)
	{
		ft_printf("%s", "Error\n");
		mlx_terminate(mlx);
		return EXIT_FAILURE;
	}

	char	**map = read_map("map.ber");
	if (!map)
	{
		mlx_delete_texture(wall_texture);
		mlx_terminate(mlx);
		return EXIT_FAILURE;
	}
	
	ft_printf("%s", *map);
	draw_map(map, mlx, wall_texture, player_texture);

	mlx_key_hook(mlx, my_keyhook, mlx);
	mlx_loop(mlx);


	for (int i = 0; map[i]; i++)
		free(map[i]);
	free(map);
	mlx_delete_texture(wall_texture);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}
