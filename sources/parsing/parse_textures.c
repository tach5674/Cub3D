/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzohraby <mzohraby@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 12:09:25 by ggevorgi          #+#    #+#             */
/*   Updated: 2025/08/31 19:03:54 by mzohraby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

bool	is_texture_line(char *line)
{
	if (!line)
		return (false);
	return (ft_strncmp(line, "NO ", 3) == 0 || ft_strncmp(line, "SO ", 3) == 0
		|| ft_strncmp(line, "WE ", 3) == 0 || ft_strncmp(line, "EA ", 3) == 0);
}


int	parse_texture_line(char *line, t_data *data)
{
	char	**split;
	char	*key;
	char	*value;

	split = ft_split(line, ' ');
	if (!split || !split[0] || !split[1] || split[2])
		return (printf("Error\nInvalid texture line: %s\n", line),
			ft_free_split(split), -1);
	key = split[0];
	value = split[1];
	if (ft_strcmp(key, "NO") == 0 && !data->textures.no)
		data->textures.no = ft_strdup(value);
	else if (ft_strcmp(key, "SO") == 0 && !data->textures.so)
		data->textures.so = ft_strdup(value);
	else if (ft_strcmp(key, "WE") == 0 && !data->textures.we)
		data->textures.we = ft_strdup(value);
	else if (ft_strcmp(key, "EA") == 0 && !data->textures.ea)
		data->textures.ea = ft_strdup(value);
	else
		return (printf("Error\nUnknown texture key: %s\n", key),
			ft_free_split(split), -1);
	ft_free_split(split);
	return (0);
}

bool	is_color_line(char *line)
{
	if (!line)
		return (false);
	return (ft_strncmp(line, "F ", 2) == 0 || ft_strncmp(line, "C ", 2) == 0);
}

static bool	parse_color(t_color *color, char *splitted_rgb)
{
	char	**rgb;

	rgb = ft_split(splitted_rgb, ',');
	if (!rgb || !rgb[0] || !rgb[1] || !rgb[2] || rgb[3])
	{
		ft_free_split(rgb);
		return (printf("Error\nInvalid RGB format: %s\n", splitted_rgb), false);
	}
	color->r = ft_custom_atoi(rgb[0]);
	color->g = ft_custom_atoi(rgb[1]);
	color->b = ft_custom_atoi(rgb[2]);
	if (color->r < 0 || color->r > 255 || color->g < 0 || color->g > 255
		|| color->b < 0 || color->b > 255)
		return (ft_free_split(rgb), printf("Error\nRGB out of range: %d,%d,%d\n", color->r,
				color->g, color->b), false);
	ft_free_split(rgb);
	return (true);
}

int	parse_color_line(char *line, t_data *data)
{
	t_color	color;
	char	**split;

	color.r = 0;
	color.g = 0; 
	color.b = 0;
	split = ft_split(line, ' ');
	if (!split || !split[0] || !split[1] || split[2])
		return (ft_free_split(split), printf("Error\nInvalid color line: %s\n", line), -1);
	if (!parse_color(&color, split[1]))
		return (ft_free_split(split), -1);
	if (ft_strcmp(split[0], "F") == 0)
		data->floor_color = color;
	else if (line[0] == 'C')
		data->ceiling_color = color;
	else
		return (printf("Error\nUnknown color key: %c	\n", line[0]), -1);
	return (0);
}
