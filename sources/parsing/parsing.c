/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggevorgi <sp1tak.gg@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 13:04:11 by mzohraby          #+#    #+#             */
/*   Updated: 2025/06/23 16:11:53 by ggevorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static char	*trim_newline(char *line)
{
	int	len = ft_strlen(line);
	if (len > 0 && line[len - 1] == '\n')
		line[len - 1] = '\0';
	return (line);
}

#include <stdbool.h>

bool	is_texture_line(char *line)
{
	if (!line)
		return (false);
	return (
		ft_strncmp(line, "NO ", 3) == 0 ||
		ft_strncmp(line, "SO ", 3) == 0 ||
		ft_strncmp(line, "WE ", 3) == 0 ||
		ft_strncmp(line, "EA ", 3) == 0
	);
}

void	ft_free_split(char **arr)
{
	int	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}

int	parse_texture_line(char *line, t_data *data)
{
	char	**split;
	char	*key;
	char	*value;

	split = ft_split(line, ' ');
	if (!split || !split[0] || !split[1] || split[2])
		return (printf("Error\nInvalid texture line: %s\n", line), -1);

	key = split[0];
	value = split[1];

	if (ft_strcmp(key, "NO") == 0)
		data->textures.no = ft_strdup(value);
	else if (ft_strcmp(key, "SO") == 0)
		data->textures.so = ft_strdup(value);
	else if (ft_strcmp(key, "WE") == 0)
		data->textures.we = ft_strdup(value);
	else if (ft_strcmp(key, "EA") == 0)
		data->textures.ea = ft_strdup(value);
	else
		return (printf("Error\nUnknown texture key: %s\n", key), -1);

	ft_free_split(split);
	return (0);
}

bool	is_color_line(char *line)
{
	if (!line)
		return (false);
	return (
		ft_strncmp(line, "F ", 2) == 0 ||
		ft_strncmp(line, "C ", 2) == 0
	);
}

int	parse_color_line(char *line, t_data *data)
{
	char	**split;
	char	**rgb;
	int		r, g, b;

	split = ft_split(line, ' ');
	if (!split || !split[0] || !split[1] || split[2])
		return (printf("Error\nInvalid color line: %s\n", line), -1);
	rgb = ft_split(split[1], ',');
	if (!rgb || !rgb[0] || !rgb[1] || !rgb[2] || rgb[3])
		return (printf("Error\nInvalid RGB format: %s\n", split[1]), -1);
	r = ft_atoi(rgb[0]);
	g = ft_atoi(rgb[1]);
	b = ft_atoi(rgb[2]);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		return (printf("Error\nRGB out of range: %d,%d,%d\n", r, g, b), -1);
	if (ft_strcmp(split[0], "F") == 0)
		data->floor_color = (t_color){r, g, b};
	else if (ft_strcmp(split[0], "C") == 0)
		data->ceiling_color = (t_color){r, g, b};
	else
		return (printf("Error\nUnknown color key: %s\n", split[0]), -1);
	ft_free_split(rgb);
	ft_free_split(split);
	return (0);
}

bool	is_map_line(char *line)
{
	int	i;

	if (!line)
		return (false);
	i = 0;
	while (line[i])
	{
		if (line[i] != '0' &&
			line[i] != '1' &&
			line[i] != ' ' &&
			line[i] != 'N' &&
			line[i] != 'S' &&
			line[i] != 'E' &&
			line[i] != 'W')
			return (false);
		i++;
	}
	return (true);
}

int	parse_config(int fd, t_data *data)
{
	char	*line;
	t_line	*map_lines = NULL;
	bool	map_started = false;

	while ((line = get_next_line(fd)) != NULL)
	{
		line = trim_newline(line);
		if (!map_started && ft_strlen(line) == 0)
		{
			free(line);
			continue;
		}
		if (is_map_line(line))
		{
			map_started = true;
			ft_lstadd_back(&map_lines, ft_lstnew(ft_strdup(line)));
		}
		else if (!map_started && is_texture_line(line))
		{
			if (parse_texture_line(line, data) == -1)
				return (free(line), ft_lstclear(&map_lines, free), -1);
		}
		else if (!map_started && is_color_line(line))
		{
			if (parse_color_line(line, data) == -1)
				return (free(line), ft_lstclear(&map_lines, free), -1);
		}
		else
		{
			free(line);
			ft_lstclear(&map_lines, free);
			return (printf("Error\nInvalid line: %s\n", line), -1);
		}

		free(line);
	}
	if (convert_list_to_map(map_lines, &data->map) == -1)
		return (ft_lstclear(&map_lines, free), -1);
	ft_lstclear(&map_lines, free);
	return (0);
}

