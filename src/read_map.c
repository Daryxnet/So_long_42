/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagarmil <dagarmil@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 15:51:44 by dagarmil          #+#    #+#             */
/*   Updated: 2024/09/13 15:52:00 by dagarmil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include "MLX42.h"
#include "get_next_line.h"

#define WIDTH 1500
#define HEIGHT 1400

void my_keyhook(mlx_key_data_t keydata, void* param)
{
    if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
        mlx_close_window((mlx_t*)param);
}

void draw_map(char **map, mlx_t* mlx, mlx_texture_t* wall_texture)
{
    int tile_size = 64; // Tamaño de cada tile (asumiendo 64x64 píxeles)
    int y = 0;

    while (map[y])
    {
        int x = 0;
        while (map[y][x])
        {
            if (map[y][x] == '1')
            {
                mlx_image_t* wall = mlx_texture_to_image(mlx, wall_texture);
                if (wall)
                {
                    mlx_image_to_window(mlx, wall, x * tile_size, y * tile_size);
                    mlx_delete_image(mlx, wall); // Limpiamos la imagen tras dibujarla
                }
            }
            x++;
        }
        y++;
    }
}

char **read_map(const char *filename)
{
    int fd = open(filename, O_RDONLY);
    if (fd < 0)
    {
        perror("Error al abrir el archivo del mapa");
        return NULL;
    }

    char *line;
    char **map = malloc(sizeof(char*) * 100); // Asignamos espacio para el mapa
    int i = 0;

    while ((line = get_next_line(fd)) != NULL)
    {
        map[i++] = line;  // Guardamos cada línea del mapa
    }
    map[i] = NULL;  // Terminamos el array con NULL
    close(fd);
    return map;
}

int32_t	main(void)
{
    mlx_t*	mlx;

    if (!(mlx = mlx_init(WIDTH, HEIGHT, "Mapa de Juego", false)))
        return (EXIT_FAILURE);

    mlx_texture_t* wall_texture = mlx_load_png("wall_jung.png");
    if (!wall_texture)
    {
        fprintf(stderr, "Error al cargar la textura de la pared\n");
        mlx_terminate(mlx);
        return EXIT_FAILURE;
    }

    // Leemos el mapa desde un archivo .ber
    char **map = read_map("mapa.ber");
    if (!map)
    {
        mlx_delete_texture(wall_texture);
        mlx_terminate(mlx);
        return EXIT_FAILURE;
    }

    // Dibujamos el mapa
    draw_map(map, mlx, wall_texture);

    mlx_key_hook(mlx, my_keyhook, mlx);
    mlx_loop(mlx);

    // Limpiamos memoria
    for (int i = 0; map[i]; i++)
        free(map[i]);
    free(map);

    mlx_delete_texture(wall_texture);
    mlx_terminate(mlx);
    return (EXIT_SUCCESS);
}

