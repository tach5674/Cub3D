/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggevorgi <sp1tak.gg@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 13:04:11 by mzohraby          #+#    #+#             */
/*   Updated: 2025/07/02 17:10:13 by ggevorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

static int	handle_map_line(char *line, t_line **map_lines)
{
	t_line	*new_node;
	char	*copy;

	copy = ft_strdup(line);
	if (!copy)
		return (printf("Error\nMemory allocation failed\n"),
			-1);
	new_node = ft_lstnew(copy);
	if (!new_node)
	{
		free(copy);
		return (printf("Error\nMemory allocation failed\n"), -1);
	}
	ft_lstadd_back(map_lines, new_node);
	return (0);
}

static int	handle_non_map_line(char *line, t_data *data)
{
	if (is_texture_line(line))
	{
		if (parse_texture_line(line, data) == -1)
			return (-1);
	}
	else if (is_color_line(line))
	{
		if (parse_color_line(line, data) == -1)
			return (-1);
	}
	else
	{
		printf("Error\nInvalid line: %s\n", line);
		return (-1);
	}
	return (0);
}

static int	process_line(char *line, bool *map_started,
	t_line **map_lines, t_data *data)
{
	int	result;

	if (!*map_started && ft_strlen(line) == 0)
		return (1);
	if (is_map_line(line))
	{
		*map_started = true;
		result = handle_map_line(line, map_lines);
		if (result == -1)
			return (-1);
	}
	else if (!*map_started)
	{
		result = handle_non_map_line(line, data);
		if (result == -1)
			return (-1);
	}
	else
	{
		printf("Error\nInvalid line: %s\n", line);
		return (-1);
	}
	return (0);
}

int	parse_config(int fd, t_data *data)
{
	char	*line;
	t_line	*map_lines;
	bool	map_started;
	int		result;

	map_lines = NULL;
	map_started = false;
	line = get_next_line(fd);
	while (line != NULL)
	{
		line = trim_newline(line);
		result = process_line(line, &map_started, &map_lines, data);
		if (result == -1)
			return (free(line), ft_lstclear(&map_lines, free), -1);
		free(line);
		line = get_next_line(fd);
	}
	if (!convert_list_to_map(map_lines, &data->map))
	{
		ft_lstclear(&map_lines, free);
		return (-1);
	}
	ft_lstclear(&map_lines, free);
	return (0);
}
