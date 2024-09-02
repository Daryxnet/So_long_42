/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagarmil <dagarmil@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 16:07:41 by dagarmil          #+#    #+#             */
/*   Updated: 2024/08/22 16:40:10 by dagarmil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minilibx/mlx.h"

int	main()
{
	void	*mlx_connection;
	void	*mlx_window;

	mlx_connection = mlx_init();
	mlx_window = mlx_new_window(mlx_connection, 1000, 1000, "My Window");

	for (int i = 0; i < 100; i++)
	{
		mlx_pixel_put(mlx_connection, mlx_window, 600 + i, 600 + i, 0xff0000);
	}


	mlx_loop(mlx_connection);

	return (0);
}
