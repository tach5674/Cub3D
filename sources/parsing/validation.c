/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggevorgi <sp1tak.gg@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 11:26:06 by ggevorgi          #+#    #+#             */
/*   Updated: 2025/07/07 12:10:49 by ggevorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

#include "cub3d.h"

static bool	is_valid_char(char c)
{
	return (c == '0' || c == '1' || c == ' '
		|| c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

static bool	check_borders(t_map *map)
{
	int	y;
	int	x;
	int	width;

	y = 0;
	while (y < map->height)
	{
		x = 0;
		width = (int)ft_strlen(map->map[y].line);
		while (x < width)
		{
			if ((y == 0 || y == map->height - 1 || x == 0 || x == width - 1)
				&& map->map[y].line[x] != '1' && map->map[y].line[x] != ' ')
				return (false);
			x++;
		}
		y++;
	}
	return (true);
}

static bool	check_player(t_map *map)
{
	int		count;
	int		y;
	int		x;

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

bool	validate_map(t_data *data)
{
	if (!check_chars(&data->map))
		return (error_msg("Invalid characters in map"));
	if (!check_player(&data->map))
		return (error_msg("Map must have exactly one player"));
	if (!check_borders(&data->map))
		return (error_msg("Map must be surrounded by walls"));
	return (true);
}