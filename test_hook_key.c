
#include <stdlib.h>
#include <stdio.h>
#include <stdio.h>
#include "MLX42.h"
#define WIDTH 2304
#define HEIGHT 1296

void my_keyhook(mlx_key_data_t keydata, void* param)
{
	// If we PRESS the 'ESCAPE' key, close Window.
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		mlx_close_window((mlx_t*)param);

	// If we PRESS the 'W' key, print "UP".
	if (keydata.key == MLX_KEY_W && keydata.action == MLX_PRESS)
		puts("UP");

	// If we PRESS the 'S' key, print "Down".
	if (keydata.key == MLX_KEY_S && keydata.action == MLX_PRESS)
		puts("Down");

	// If we PRESS the 'A' key, print "Left".
	if (keydata.key == MLX_KEY_A && keydata.action == MLX_PRESS)
		puts("Left");

	// If we PRESS the 'D' key, print "Right".
	if (keydata.key == MLX_KEY_D && keydata.action == MLX_PRESS)
		puts("Right");
}

int32_t	main(void)
{
	mlx_t*	mlx;

	if (!(mlx = mlx_init(WIDTH, HEIGHT, "Window w B", false)))
		return (EXIT_FAILURE);

	mlx_texture_t* texture = mlx_load_png("image.png");
	if (!texture)
	{
		fprintf(stderr, "Error\n");
		mlx_terminate(mlx);
		return EXIT_FAILURE;
	}
	mlx_image_t* fondo = mlx_texture_to_image(mlx, texture);
    if (!fondo)
    {
        fprintf(stderr, "Error al cargar la imagen PNG\n");
		mlx_delete_texture(texture);
        mlx_terminate(mlx);
        return EXIT_FAILURE;
    }
	mlx_delete_texture(texture);

    // Pinta la imagen cargada en la ventana
    if (mlx_image_to_window(mlx, fondo, 0, 0) < 0)
    {
        fprintf(stderr, "Error al pintar la imagen en la ventana\n");
		mlx_delete_image(mlx, fondo);
        mlx_terminate(mlx);
        return EXIT_FAILURE;
    }

	mlx_key_hook(mlx, my_keyhook, mlx);
	mlx_loop(mlx);
	mlx_delete_image(mlx, fondo);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}
