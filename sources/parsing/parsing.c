/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggevorgi <sp1tak.gg@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 13:04:11 by mzohraby          #+#    #+#             */
/*   Updated: 2025/07/02 12:44:25 by ggevorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//parse_color_texture

bool	is_map_line(char *line)
{
	int	i;

	if (!line)
		return (false);
	i = 0;
	while (line[i])
	{
		if (line[i] != '0'
			&& line[i] != '1'
			&& line[i] != ' '
			&& line[i] != 'N'
			&& line[i] != 'S'
			&& line[i] != 'E'
			&& line[i] != 'W')
			return (false);
		i++;
	}
	return (true);
}

int	parse_config(int fd, t_data *data)
{
	char	*line;
	t_line	*map_lines;
	bool	map_started;
	t_line *new_node;

	map_lines = NULL;
	map_started = false;
	while ((line = get_next_line(fd)) != NULL)
	{
		line = trim_newline(line);
		if (!map_started && ft_strlen(line) == 0)
		{
			free(line);
			continue ;
		}
		if (is_map_line(line))
		{
			map_started = true;
			char *copy = ft_strdup(line);
			if (!copy)
			{
				printf("Error\nMemory allocation failed\n");
				return (free(line), ft_lstclear(&map_lines, free), -1);
			}
			new_node = ft_lstnew(copy);
			if (!new_node)
			{
				printf("Error\nMemory allocation failed\n");
				free(copy);
				return (free(line), ft_lstclear(&map_lines, free), -1);
			}
			ft_lstadd_back(&map_lines, new_node);
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
			printf("Error\nInvalid line: %s\n", line);
			return (free(line), ft_lstclear(&map_lines, free), -1);
		}
		free(line);
	}
	if (!convert_list_to_map(map_lines, &data->map))
	{
		ft_lstclear(&map_lines, free);		
		return (-1);
	}
	ft_lstclear(&map_lines, free);
	return (0);
}
