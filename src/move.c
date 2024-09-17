#include <stdio.h>
#include "MLX42.h"

#define WIDTH 1500
#define HEIGHT 1400

// Estructura para el jugador
typedef struct s_player {
    int x;
    int y;
} t_player;

// Función para mover al jugador
void move_player(t_player *player, char **map, int new_x, int new_y)
{
    if (map[new_y][new_x] != '1')  // Si no es una pared
    {
        player->x = new_x;
        player->y = new_y;
        printf("Player moved to (%d, %d)\n", new_x, new_y);
    }
    else
    {
        printf("Wall at (%d, %d), can't move!\n", new_x, new_y);
    }
}

// Función para manejar las teclas
void my_keyhook(mlx_key_data_t keydata, void* param)
{
    t_player *player = (t_player *)param;
    char **map = ...;  // Aquí debes tener el mapa cargado

    if (keydata.action == MLX_PRESS)
    {
        if (keydata.key == MLX_KEY_W) // Mover hacia arriba
            move_player(player, map, player->x, player->y - 1);
        if (keydata.key == MLX_KEY_S) // Mover hacia abajo
            move_player(player, map, player->x, player->y + 1);
        if (keydata.key == MLX_KEY_A) // Mover hacia la izquierda
            move_player(player, map, player->x - 1, player->y);
        if (keydata.key == MLX_KEY_D) // Mover hacia la derecha
            move_player(player, map, player->x + 1, player->y);
    }
}

// Función principal
int32_t main(void)
{
    mlx_t *mlx;
    t_player player = {1, 1};  // Posición inicial del jugador

    // Inicializar ventana y cargar mapa (aquí debes cargar tu mapa en 'map')
    char *map[] = {
        "1111111",
        "1P0C001",
        "1000001",
        "1C0E001",
        "1111111",
    };

    // Inicializar MLX
    mlx = mlx_init(WIDTH, HEIGHT, "Window w B", false);
    if (!mlx)
        return (EXIT_FAILURE);

    // Hook para las teclas
    mlx_key_hook(mlx, my_keyhook, &player);

    // Loop de la ventana
    mlx_loop(mlx);
    mlx_terminate(mlx);
    return (EXIT_SUCCESS);
}

