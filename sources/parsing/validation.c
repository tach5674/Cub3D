/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzohraby <mzohraby@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 11:26:06 by ggevorgi          #+#    #+#             */
/*   Updated: 2025/08/17 17:18:10 by mzohraby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static bool	check_player(t_map *map)
{
	int	count;
	int	y;
	int	x;

	count = 0;
	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (map->map[y].line[x])
		{
			if (map->map[y].line[x] == 'N' || map->map[y].line[x] == 'S'
				|| map->map[y].line[x] == 'E' || map->map[y].line[x] == 'W')
			{
				count++;
				map->player.x = x;
				map->player.y = y;
				map->player.dir = map->map[y].line[x];
			}
			x++;
		}
		y++;
	}
	return (count == 1);
}

static bool	check_chars(t_map *map)
{
	int	y;
	int	x;

	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (map->map[y].line[x])
		{
			if (!is_valid_char(map->map[y].line[x]))
				return (false);
			x++;
		}
		y++;
	}
	return (true);
}

void	flood_fill(char **temp_map, t_point p, int height, int width)
{
	if (p.y < 0 || p.y >= height || p.x < 0 || p.x >= width
		|| temp_map[p.y][p.x] == '1' || temp_map[p.y][p.x] == 'F')
		return ;
	temp_map[p.y][p.x] = 'F';
	flood_fill(temp_map, (t_point){p.y - 1, p.x}, height, width);
	flood_fill(temp_map, (t_point){p.y + 1, p.x}, height, width);
	flood_fill(temp_map, (t_point){p.y, p.x - 1}, height, width);
	flood_fill(temp_map, (t_point){p.y, p.x + 1}, height, width);
}

bool	validate_map(t_data *data)
{
	if (!check_chars(&data->map))
		return (error_msg("Invalid characters in map"));
	if (!check_player(&data->map))
		return (error_msg("Map must have exactly one player"));
	if (!check_borders(&data->map))
		return (error_msg("Map must be surrounded by walls"));
	if (!check_map_closed(&data->map))
		return (error_msg("Map is not closed - player can escape"));
	return (true);
}
