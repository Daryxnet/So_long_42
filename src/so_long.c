/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagarmil <dagarmil@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 15:52:18 by dagarmil          #+#    #+#             */
/*   Updated: 2024/09/17 12:51:08 by dagarmil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdlib.h>
#include "MLX42.h"
#include "libft.h"
#define WIDTH 1500
#define HEIGHT 1000
#define TILE_SIZE 200  // Definir tamaño del tile

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
	mlx_image_t *bg_image;
	mlx_image_t *wall_image;
	mlx_image_t *player_image;
	mlx_image_t *player_d_image;
	mlx_image_t *collect_image;
} t_game;

void draw_map(t_game *game);

// Mover jugador
void move_player(t_game *game, int new_x, int new_y)
{
	char **map = game->map;
	if (map[new_y][new_x] != '1') // Si no es una pared
	{
		map[game->player.y][game->player.x] = '0';  // Limpiar la posición anterior

		game->player.x = new_x;
		game->player.y = new_y;
		map[new_y][new_x] = 'P';  // Actualizar la nueva posición
		ft_printf("Player moved to (%d, %d)\n", new_x, new_y);
		mlx_image_to_window(game->mlx, game->bg_image, 0, 0);  // Redibujar fondo
		draw_map(game);  // Redibujar todo el mapa
	}
	else
	{
		ft_printf("Wall at (%d, %d), can't move!\n", new_x, new_y);
	}
}

// Manejar teclas
void my_keyhook(mlx_key_data_t keydata, void* param)
{
	t_game *game = (t_game *)param;

	if (keydata.action == MLX_PRESS)
	{
		if (keydata.key == MLX_KEY_ESCAPE)
			mlx_close_window(game->mlx);

		// Movimiento del jugador
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

// Dibujar mapa
void draw_map(t_game *game)
{
	int y = 0;
	while (game->map[y])
	{
		int x = 0;
		while (game->map[y][x])
		{
			mlx_image_to_window(game->mlx, game->bg_image, x * TILE_SIZE, y * TILE_SIZE);
			// Dibujar la pared
			if (game->map[y][x] == '1')
				mlx_image_to_window(game->mlx, game->wall_image, x * TILE_SIZE, y * TILE_SIZE);
			// Dibujar el jugador
			else if (game->map[y][x] == 'P')
			{
				mlx_image_to_window(game->mlx, game->player_image, x * TILE_SIZE, y * TILE_SIZE);
			}
			// Dibujar el coleccionable
			else if (game->map[y][x] == 'C')
				mlx_image_to_window(game->mlx, game->collect_image, x * TILE_SIZE, y * TILE_SIZE);
			x++;
		}
		y++;
	}
}

// Leer mapa desde archivo
char **read_map(const char *filename)
{
	int	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		ft_printf("Error reading map\n");
		return NULL;
	}

	char **map = malloc(sizeof(char*) * 100);  // Ajusta el tamaño según el mapa
	if (!map)
		return NULL;

	char *line;
	int i = 0;
	while ((line = get_next_line(fd)) != NULL)
		map[i++] = line;
	map[i] = NULL;

	close(fd);
	return map;
}

int32_t main(void)
{
	mlx_t *mlx = mlx_init(WIDTH, HEIGHT, "So_long Optimized", false);
	if (!mlx)
		return EXIT_FAILURE;

	// Cargar texturas y convertir a imágenes una sola vez
	mlx_texture_t *bg_texture = mlx_load_png("bg.png");
	mlx_texture_t *wall_texture = mlx_load_png("wall_jung.png");
	mlx_texture_t *player_texture = mlx_load_png("player.png");
	mlx_texture_t *player_d_texture = mlx_load_png("player_down1.png");
	mlx_texture_t *collect_texture = mlx_load_png("Gold.png");

	if (!bg_texture || !wall_texture || !player_texture || !collect_texture)
	{
		ft_printf("Error loading textures\n");
		mlx_terminate(mlx);
		return EXIT_FAILURE;
	}

	t_game game;
	game.mlx = mlx;

	// Convertir texturas a imágenes
	game.bg_image = mlx_texture_to_image(mlx, bg_texture);
	game.wall_image = mlx_texture_to_image(mlx, wall_texture);
	game.player_image = mlx_texture_to_image(mlx, player_texture);
	game.player_d_image = mlx_texture_to_image(mlx, player_d_texture);
	game.collect_image = mlx_texture_to_image(mlx, collect_texture);

	// Leer mapa
	game.map = read_map("map.ber");
	if (!game.map)
	{
		ft_printf("Error reading map\n");
		mlx_terminate(mlx);
		return EXIT_FAILURE;
	}

	// Encontrar posición inicial del jugador
	int y = 0;
	while (game.map[y])
	{
		int x = 0;
		while (game.map[y][x])
		{
			if (game.map[y][x] == 'P')
			{
				game.player.x = x;
				game.player.y = y;
				break;
			}
			x++;
		}
		y++;
	}

	// Dibujar fondo e inicializar mapa
	mlx_image_to_window(mlx, game.bg_image, 0, 0);
	draw_map(&game);

	// Asignar función de teclas y comenzar loop
	mlx_key_hook(mlx, my_keyhook, &game);
	mlx_loop(mlx);

	// Liberar memoria y texturas
	int i = 0;
	while (game.map[i])
		free(game.map[i++]);
	free(game.map);
	mlx_terminate(mlx);

	return EXIT_SUCCESS;
}

