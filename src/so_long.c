/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagarmil <dagarmil@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 15:52:18 by dagarmil          #+#    #+#             */
/*   Updated: 2024/09/17 16:14:44 by dagarmil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "MLX42.h"
#include "libft.h"
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
	mlx_image_t *player_down_image;  // Imagen del jugador mirando abajo
	mlx_image_t *player_up_image;    // Imagen del jugador mirando arriba
	mlx_image_t *player_left_image;  // Imagen del jugador mirando izquierda
	mlx_image_t *player_right_image; // Imagen del jugador mirando derecha
	mlx_image_t *collect_image;
} t_game;

// Prototypes
void draw_tile(t_game *game, int x, int y);
void draw_map(t_game *game);
void move_player(t_game *game, int new_x, int new_y);

// Mover jugador
void move_player(t_game *game, int new_x, int new_y)
{
	char **map = game->map;

	// Verificar que la nueva posición no sea una pared
	if (map[new_y][new_x] != '1') {
		// Limpiar el sprite del jugador anterior dibujando solo el fondo
		mlx_image_to_window(game->mlx, game->bg_image, game->player.x * TILE_SIZE, game->player.y * TILE_SIZE);

		// Si hay un coleccionable en la posición anterior, redibujarlo
		if (game->map[game->player.y][game->player.x] == 'C')
			mlx_image_to_window(game->mlx, game->collect_image, game->player.x * TILE_SIZE, game->player.y * TILE_SIZE);

		// Actualizar la posición del jugador en el mapa
		map[game->player.y][game->player.x] = '0';  // Limpiar posición anterior
		game->player.x = new_x;
		game->player.y = new_y;
		map[new_y][new_x] = 'P';  // Nueva posición

		// Redibujar el jugador en la nueva posición
		draw_tile(game, new_x, new_y);

		ft_printf("Player moved to (%d, %d)\n", new_x, new_y);
	} else {
		ft_printf("Wall at (%d, %d), can't move!\n", new_x, new_y);
	}
}

// Dibujar un tile específico en (x, y)
void draw_tile(t_game *game, int x, int y)
{
	// Redibujar el fondo
	mlx_image_to_window(game->mlx, game->bg_image, x * TILE_SIZE, y * TILE_SIZE);

	// Dibujar el elemento correspondiente
	if (game->map[y][x] == '1')
		mlx_image_to_window(game->mlx, game->wall_image, x * TILE_SIZE, y * TILE_SIZE);
	else if (game->map[y][x] == 'P')
		mlx_image_to_window(game->mlx, game->player.current_image, x * TILE_SIZE, y * TILE_SIZE);  // Usar la imagen actual del jugador
	else if (game->map[y][x] == 'C')
		mlx_image_to_window(game->mlx, game->collect_image, x * TILE_SIZE, y * TILE_SIZE);
}

// Dibujar el mapa completo (solo al inicio)
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

// Manejar teclas
void my_keyhook(mlx_key_data_t keydata, void* param)
{
	t_game *game = (t_game *)param;

	if (keydata.action == MLX_PRESS) {
		if (keydata.key == MLX_KEY_ESCAPE)
			mlx_close_window(game->mlx);
		// Movimiento del jugador y cambiar sprite según la dirección
		else if (keydata.key == MLX_KEY_W) {
			game->player.current_image = game->player_up_image;   // Cambiar a sprite mirando hacia arriba
			move_player(game, game->player.x, game->player.y - 1);
		}
		else if (keydata.key == MLX_KEY_S) {
			game->player.current_image = game->player_down_image; // Cambiar a sprite mirando hacia abajo
			move_player(game, game->player.x, game->player.y + 1);
		}
		else if (keydata.key == MLX_KEY_A) {
			game->player.current_image = game->player_left_image; // Cambiar a sprite mirando hacia la izquierda
			move_player(game, game->player.x - 1, game->player.y);
		}
		else if (keydata.key == MLX_KEY_D) {
			game->player.current_image = game->player_right_image;// Cambiar a sprite mirando hacia la derecha
			move_player(game, game->player.x + 1, game->player.y);
		}
	}
}

// Leer mapa desde archivo
char **read_map(const char *filename)
{
	int fd = open(filename, O_RDONLY);
	if (fd < 0) {
		ft_printf("Error reading map\n");
		return NULL;
	}

	char **map = NULL;
	char *line;
	int i = 0;

	// Leer líneas hasta el final del archivo
	while ((line = get_next_line(fd)) != NULL) {
		map = realloc(map, sizeof(char*) * (i + 2));  // Ajustar el tamaño dinámicamente
		map[i++] = line;
	}
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
	mlx_texture_t *player_down_texture = mlx_load_png("player_down.png");  // Sprite mirando hacia abajo
	mlx_texture_t *player_up_texture = mlx_load_png("player_up.png");      // Sprite mirando hacia arriba
	mlx_texture_t *player_left_texture = mlx_load_png("player_left.png");  // Sprite mirando hacia la izquierda
	mlx_texture_t *player_right_texture = mlx_load_png("player_right.png");// Sprite mirando hacia la derecha
	mlx_texture_t *collect_texture = mlx_load_png("Gold.png");

	if (!bg_texture || !wall_texture || !player_down_texture || !player_up_texture ||
		!player_left_texture || !player_right_texture || !collect_texture) {
		ft_printf("Error loading textures\n");
		mlx_terminate(mlx);
		return EXIT_FAILURE;
	}

	t_game game;
	game.mlx = mlx;

	// Convertir texturas a imágenes
	game.bg_image = mlx_texture_to_image(mlx, bg_texture);
	game.wall_image = mlx_texture_to_image(mlx, wall_texture);
	game.player_down_image = mlx_texture_to_image(mlx, player_down_texture);
	game.player_up_image = mlx_texture_to_image(mlx, player_up_texture);
	game.player_left_image = mlx_texture_to_image(mlx, player_left_texture);
	game.player_right_image = mlx_texture_to_image(mlx, player_right_texture);
	game.collect_image = mlx_texture_to_image(mlx, collect_texture);

	// Configurar imagen actual del jugador
	game.player.current_image = game.player_down_image; // Por defecto mirando hacia abajo

	// Leer mapa
	game.map = read_map("map.ber");
	if (!game.map) {
		ft_printf("Error reading map\n");
		mlx_terminate(mlx);
		return EXIT_FAILURE;
	}

	// Encontrar posición inicial del jugador
	int y = 0;
	while (game.map[y]) {
		int x = 0;
		while (game.map[y][x]) {
			if (game.map[y][x] == 'P') {
				game.player.x = x;
				game.player.y = y;
				break;
			}
			x++;
		}
		y++;
	}

	// Dibujar el mapa inicialmente
	draw_map(&game);

	// Asignar función de teclas y comenzar loop
	mlx_key_hook(mlx, my_keyhook, &game);
	mlx_loop(mlx);

	// Liberar memoria y texturas
	y = 0;
	while (game.map[y])
		free(game.map[y++]);
	free(game.map);

	mlx_terminate(mlx);
	return EXIT_SUCCESS;
}
