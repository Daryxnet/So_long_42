/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagarmil <dagarmil@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 16:07:05 by dagarmil          #+#    #+#             */
/*   Updated: 2024/09/19 16:07:34 by dagarmil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include <fcntl.h>

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

    while ((line = get_next_line(fd)) != NULL) {
        map = realloc(map, sizeof(char*) * (i + 2));
        map[i++] = line;
    }
    map[i] = NULL;

    close(fd);
    return map;
}
