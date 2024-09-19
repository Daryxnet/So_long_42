/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagarmil <dagarmil@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 16:05:52 by dagarmil          #+#    #+#             */
/*   Updated: 2024/09/19 16:06:14 by dagarmil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int32_t main(void)
{
    mlx_t *mlx = mlx_init(WIDTH, HEIGHT, "So_long Optimized", false);
    if (!mlx)
        return EXIT_FAILURE;

    // Cargar texturas
    mlx_texture_t *bg_texture = mlx_load_png("bg.png");
    mlx_texture_t *wall_texture = mlx_load_png("wall_jung.png");
    mlx_texture_t *player_down_texture = mlx_load_png("sprites/characters/Cowboy/walk/player_down.png");
    mlx_texture_t *player_up_texture = mlx_load_png("sprites/characters/Cowboy/walk/player_up.png");
    mlx_texture_t *player_left_texture = mlx_load_png("sprites/characters/Cowboy/walk/player_left.png");
    mlx_texture_t *player_right_texture = mlx_load_png("sprites/characters/Cowboy/walk/player_right.png");
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

    game.player.current_image = game.player_down_image;

    // Leer el mapa
    game.map = read_map("map.ber");
    if (!game.map) {
        ft_printf("Error reading map\n");
        mlx_terminate(mlx);
        return EXIT_FAILURE;
    }

    // Dibujar el mapa
    draw_map(&game);

    // Asignar función de teclas y comenzar el loop
    mlx_key_hook(mlx, my_keyhook, &game);
    mlx_loop(mlx);

    // Liberar memoria
    int y = 0;
    while (game.map[y])
        free(game.map[y++]);
    free(game.map);

    mlx_terminate(mlx);
    return EXIT_SUCCESS;
}
