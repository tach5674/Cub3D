/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzohraby <mzohraby@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 13:21:21 by mikayel           #+#    #+#             */
/*   Updated: 2025/07/25 12:51:01 by mzohraby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// int	ft_strcmp(const char *s1, const char *s2)
// {
// 	size_t	i;

// 	i = -1;
// 	while (s1[i] || s2[i])
// 		if (s1[i] != s2[i])
// 			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
// 	return (0);
// }

int	get_number(t_map *map, int map_x, int map_y)
{
	if (!map || map_x < 0 || map_y < 0)
	{
		printf("out\n");
		return -1;
	}
	if (map_y >= map->height || map_x >= map->map[map_y].line_length)
	{
		printf("out\n");
		return -1; // out of bounds or malformed line
	}
	if (map->map[map_y].line[map_x] == ' ')
		return (1);
	return (map->map[map_y].line[map_x] - '0');
}
