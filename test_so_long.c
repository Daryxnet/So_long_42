#include "MLX42.h"
#include <stdio.h>
#include <stdlib.h>

// Esta función se llama cada vez que se presiona una tecla
void handle_key(mlx_key_data_t keydata, void* param)
{
    if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
    {
        mlx_close_window((mlx_t*)param);
    }
}

int32_t main(void)
{
    // Inicializa MLX y crea una ventana de 800x600
    mlx_t* mlx = mlx_init(800, 600, "Ventana MLX42", true);
    if (!mlx)
    {
        fprintf(stderr, "Error al inicializar MLX42\n");
        return EXIT_FAILURE;
    }

    // Asigna la función de manejo de teclas
    mlx_key_hook(mlx, handle_key, mlx);

    // Comienza el loop principal
    mlx_loop(mlx);

    // Limpia y libera recursos al cerrar la ventana
    mlx_terminate(mlx);
    return EXIT_SUCCESS;
}

