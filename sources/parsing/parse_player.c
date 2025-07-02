/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_player.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggevorgi <sp1tak.gg@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 12:07:01 by ggevorgi          #+#    #+#             */
/*   Updated: 2025/07/02 12:17:24 by ggevorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static bool	is_player(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

static bool	set_player(bool *is_found, t_map *map, int x, int y)
{
	if (*is_found)
	{
		printf("Error\nMultiple player positions found\n");
		return (false);
	}
	map->player.x = x;
	map->player.y = y;
	map->player.dir = map->map[y].line[x];
	*is_found = true;
	return (true);
}

bool	find_player(t_map *map)
{
	int		x;
	int		y;
	bool	found;

	y = 0;
	found = false;
	map->player.dir = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->map[y].line_length)
		{
			if (is_player(map->map[y].line[x])
				&& !set_player(&found, map, x, y))
			{
				return (false);
			}
			x++;
		}
		y++;
	}
	if (!found)
		printf("Error\nNo player found in the map\n");
	return (found);
}
