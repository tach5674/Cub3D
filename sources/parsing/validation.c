/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggevorgi <sp1tak.gg@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 11:26:06 by ggevorgi          #+#    #+#             */
/*   Updated: 2025/08/16 23:02:30 by ggevorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static bool	is_valid_char(char c)
{
	return (c == '0' || c == '1' || c == '2' || c == '3' || c == ' ' || c == 'N'
		|| c == 'S' || c == 'E' || c == 'W');
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

static void	flood_fill(char **temp_map, int y, int x, int height, int width)
{
	if (y < 0 || y >= height || x < 0 || x >= width || temp_map[y][x] == '1' 
		|| temp_map[y][x] == 'F')
		return ;
	
	temp_map[y][x] = 'F';
	
	flood_fill(temp_map, y - 1, x, height, width);
	flood_fill(temp_map, y + 1, x, height, width);
	flood_fill(temp_map, y, x - 1, height, width);
	flood_fill(temp_map, y, x + 1, height, width);
}

static bool	check_map_closed(t_map *map)
{
	char	**temp_map;
	int		y;
	int		x;
	int		max_width;
	bool	is_closed;

	max_width = 0;
	y = 0;
	while (y < map->height)
	{
		x = ft_strlen(map->map[y].line);
		if (x > max_width)
			max_width = x;
		y++;
	}

	temp_map = malloc(sizeof(char *) * map->height);
	if (!temp_map)
		return (false);
	
	y = 0;
	while (y < map->height)
	{
		temp_map[y] = malloc(max_width + 1);
		if (!temp_map[y])
		{
			while (--y >= 0)
				free(temp_map[y]);
			free(temp_map);
			return (false);
		}
		ft_memset(temp_map[y], ' ', max_width);
		temp_map[y][max_width] = '\0';
		ft_strlcpy(temp_map[y], map->map[y].line, ft_strlen(map->map[y].line) + 1);
		y++;
	}
	flood_fill(temp_map, map->player.y, map->player.x, map->height, max_width);
	is_closed = true;
	y = 0;
	while (y < map->height && is_closed)
	{
		x = 0;
		while (x < max_width && is_closed)
		{
			if ((y == 0 || y == map->height - 1 || x == 0 || x == max_width - 1)
				&& temp_map[y][x] == 'F')
				is_closed = false;
			x++;
		}
		y++;
	}
	y = 0;
	while (y < map->height)
	{
		free(temp_map[y]);
		y++;
	}
	free(temp_map);

	return (is_closed);
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
