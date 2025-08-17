/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validataion_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzohraby <mzohraby@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 15:13:15 by mzohraby          #+#    #+#             */
/*   Updated: 2025/08/17 16:45:04 by mzohraby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	file_exists(const char *filename)
{
	int	fd;

	if (!filename)
		return (false);
	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		return (false);
	}
	close(fd);
	return (true);
}

bool	load_textures(t_data *data)
{
	const char	*textures[] = {data->textures.no, data->textures.so,
		data->textures.we, data->textures.ea};
	const char	*texture_names[] = {"North", "South", "West", "East"};
	int			i;

	i = 0;
	while (i < 4)
	{
		if (!file_exists(textures[i]))
		{
			printf("Error: %s texture not found: %s\n", texture_names[i],
				textures[i]);
			return (false);
		}
		i++;
	}
	return (true);
}

bool	is_valid_char(char c)
{
	return (c == '0' || c == '1' || c == '2' || c == '3' || c == ' ' || c == 'N'
		|| c == 'S' || c == 'E' || c == 'W');
}

bool	check_borders(t_map *map)
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
