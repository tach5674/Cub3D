/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggevorgi <sp1tak.gg@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 13:21:21 by mikayel           #+#    #+#             */
/*   Updated: 2025/08/31 17:49:40 by ggevorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_number(t_map *map, int map_x, int map_y)
{
	if (!map || map_x < 0 || map_y < 0)
	{
		printf("Error\nout\n");
		return (-1);
	}
	if (map_y >= map->height || map_x >= map->map[map_y].line_length)
	{
		printf("Error\nout\n");
		return (-1);
	}
	if (map->map[map_y].line[map_x] == ' ')
		return (0);
	return (map->map[map_y].line[map_x] - '0');
}
