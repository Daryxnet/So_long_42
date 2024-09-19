/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagarmil <dagarmil@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 15:52:18 by dagarmil          #+#    #+#             */
/*   Updated: 2024/09/19 10:57:30 by dagarmil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdlib.h>
#include "MLX42.h"
#include "libft.h"
#include <fcntl.h>
#define TILE_SIZE 200  // Definir tamaño del tile

// Player Struct
typedef struct s_player {
	int x;
	int y;
	mlx_image_t *current_image;  // Imagen actual del jugador
} t_player;

// Estructura del juego/mapa
typedef struct s_game {
	t_player player;
	char **map;
	int map_width;
	int map_height;
	mlx_t *mlx;
	mlx_image_t *bg_image;
	mlx_image_t *wall_image;
	mlx_image_t *player_down_image;
	mlx_image_t *player_up_image;
	mlx_image_t *player_left_image;
	mlx_image_t *player_right_image;
	mlx_image_t *collect_image;
} t_game;

int ft_max(int a, int b)
{
	if (a > b)
		return a;
	else
		return b;
}

void draw_map(t_game *game);

// Mover jugador
void move_player(t_game *game, int new_x, int new_y, mlx_image_t *new_image)
{
	char **map = game->map;
	if (map[new_y][new_x] != '1') // Si no es una pared
	{
		map[game->player.y][game->player.x] = '0';  // Limpiar la posición anterior

		// Cambiar la imagen del jugador según la dirección
		game->player.current_image = new_image;
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
			move_player(game, game->player.x, game->player.y - 1, game->player_up_image);  // Mover arriba
		else if (keydata.key == MLX_KEY_S)
			move_player(game, game->player.x, game->player.y + 1, game->player_down_image);  // Mover abajo
		else if (keydata.key == MLX_KEY_A)
			move_player(game, game->player.x - 1, game->player.y, game->player_left_image);  // Mover izquierda
		else if (keydata.key == MLX_KEY_D)
			move_player(game, game->player.x + 1, game->player.y, game->player_right_image);  // Mover derecha
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
				mlx_image_to_window(game->mlx, game->player.current_image, x * TILE_SIZE, y * TILE_SIZE);
			// Dibujar el coleccionable
			else if (game->map[y][x] == 'C')
				mlx_image_to_window(game->mlx, game->collect_image, x * TILE_SIZE, y * TILE_SIZE);
			x++;
		}
		y++;
	}
}

// Leer mapa desde archivo
char **read_map(const char *filename, t_game *game)
{
	int fd = open(filename, O_RDONLY);
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
	game->map_width = 0;
	while ((line = get_next_line(fd)) != NULL)
	{
		map[i++] = line;
		game->map_width = ft_max(game->map_width, ft_strlen(line));
	}
	map[i] = NULL;
	game->map_height = i;  // Número de filas del mapa

	close(fd);
	return map;
}

int32_t main(void)
{
	t_game game;

	// Leer mapa
	game.map = read_map("map.ber", &game);
	if (!game.map)
	{
		ft_printf("Error reading map\n");
		return EXIT_FAILURE;
	}

	// Inicializar MLX con dimensiones basadas en el mapa
	int window_width = game.map_width * TILE_SIZE;
	int window_height = game.map_height * TILE_SIZE;
	game.mlx = mlx_init(window_width, window_height, "So_long", false);
	if (!game.mlx)
		return EXIT_FAILURE;

	// Cargar texturas y convertir a imágenes una sola vez
	mlx_texture_t *bg_texture = mlx_load_png("bg.png");
	mlx_texture_t *wall_texture = mlx_load_png("wall_jung.png");
	mlx_texture_t *player_down_texture = mlx_load_png("player_down.png");  // Sprite mirando hacia abajo
	mlx_texture_t *player_up_texture = mlx_load_png("player_up.png");      // Sprite mirando hacia arriba
	mlx_texture_t *player_left_texture = mlx_load_png("player_left.png");  // Sprite mirando hacia la izquierda
	mlx_texture_t *player_right_texture = mlx_load_png("player_right.png");// Sprite mirando hacia la derecha
	mlx_texture_t *collect_texture = mlx_load_png("Gold.png");

	if (!bg_texture || !wall_texture || !player_down_texture || !player_up_texture ||
		!player_left_texture || !player_right_texture || !collect_texture) {
		ft_printf("Error loading textures\n");
		mlx_terminate(game.mlx);
		return EXIT_FAILURE;
	}

	// Convertir texturas a imágenes
	game.bg_image = mlx_texture_to_image(game.mlx, bg_texture);
	game.wall_image = mlx_texture_to_image(game.mlx, wall_texture);
	game.player_down_image = mlx_texture_to_image(game.mlx, player_down_texture);
	game.player_up_image = mlx_texture_to_image(game.mlx, player_up_texture);
	game.player_left_image = mlx_texture_to_image(game.mlx, player_left_texture);
	game.player_right_image = mlx_texture_to_image(game.mlx, player_right_texture);
	game.collect_image = mlx_texture_to_image(game.mlx, collect_texture);

	// Inicialmente, el jugador mira hacia abajo
	game.player.current_image = game.player_down_image;

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
	mlx_image_to_window(game.mlx, game.bg_image, 0, 0);
	draw_map(&game);

	// Asignar función de teclas y comenzar loop
	mlx_key_hook(game.mlx, my_keyhook, &game);
	mlx_loop(game.mlx);

	// Liberar memoria y texturas
	int i = 0;
	while (game.map[i])
		free(game.map[i++]);
	free(game.map);
	mlx_terminate(game.mlx);

	return EXIT_SUCCESS;
}
