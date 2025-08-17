/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_if_map_is_closed.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzohraby <mzohraby@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 17:14:35 by mzohraby          #+#    #+#             */
/*   Updated: 2025/08/17 17:15:12 by mzohraby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	get_max_width(t_map *map)
{
	int		max_width;
	t_point	p;

	p.y = 0;
	max_width = 0;
	while (p.y < map->height)
	{
		p.x = ft_strlen(map->map[p.y].line);
		if (p.x > max_width)
			max_width = p.x;
		p.y++;
	}
	return (max_width);
}

static void	free_temp_map(char **temp_map, int height)
{
	int	y;

	y = 0;
	while (y < height)
	{
		free(temp_map[y]);
		y++;
	}
	free(temp_map);
}

static char	**alloc_temp_map(t_map *map, int max_width)
{
	char	**temp_map;
	t_point	p;

	temp_map = malloc(sizeof(char *) * map->height);
	if (!temp_map)
		return (NULL);
	p.y = 0;
	while (p.y < map->height)
	{
		temp_map[p.y] = malloc(max_width + 1);
		if (!temp_map[p.y])
		{
			while (--p.y >= 0)
				free(temp_map[p.y]);
			free(temp_map);
			return (NULL);
		}
		ft_memset(temp_map[p.y], ' ', max_width);
		temp_map[p.y][max_width] = '\0';
		ft_strlcpy(temp_map[p.y], map->map[p.y].line,
			ft_strlen(map->map[p.y].line) + 1);
		p.y++;
	}
	return (temp_map);
}

static bool	check_borders_closed(char **temp_map, int height, int width)
{
	t_point	p;

	p.y = 0;
	while (p.y < height)
	{
		p.x = 0;
		while (p.x < width)
		{
			if ((p.y == 0 || p.y == height - 1
					|| p.x == 0 || p.x == width - 1)
				&& temp_map[p.y][p.x] == 'F')
				return (false);
			p.x++;
		}
		p.y++;
	}
	return (true);
}

bool	check_map_closed(t_map *map)
{
	char	**temp_map;
	int		max_width;
	bool	is_closed;

	max_width = get_max_width(map);
	temp_map = alloc_temp_map(map, max_width);
	if (!temp_map)
		return (false);
	flood_fill(temp_map, (t_point){map->player.y, map->player.x},
		map->height, max_width);
	is_closed = check_borders_closed(temp_map, map->height, max_width);
	free_temp_map(temp_map, map->height);
	return (is_closed);
}
