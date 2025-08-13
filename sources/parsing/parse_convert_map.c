/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_convert_map.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzohraby <mzohraby@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 12:40:42 by ggevorgi          #+#    #+#             */
/*   Updated: 2025/08/13 19:52:17 by mzohraby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static bool	validate_list_size(t_line *lst)
{
	int	count;

	count = ft_lstsize(lst);
	if (count < 3)
	{
		printf("Error\nMap must have at least 3 lines\n");
		return (false);
	}
	return (true);
}

static t_line	*allocate_map_array(int count)
{
	t_line	*result;

	result = malloc(sizeof(t_line) * count);
	if (!result)
	{
		printf("Error\nMemory allocation failed\n");
		return (NULL);
	}
	return (result);
}

static bool	copy_list_to_array(t_line *lst, t_line *result)
{
	int		i;
	t_line	*node;

	i = 0;
	node = lst;
	while (node)
	{
		result[i].line = ft_strdup(node->line);
		if (!result[i].line)
		{
			printf("Error\nMemory allocation failed\n");
			while (i-- > 0)
				free(result[i].line);
			return (false);
		}
		result[i].line_length = node->line_length;
		i++;
		node = node->next;
	}
	return (true);
}

static void	cleanup_map(t_map *map, int lines_to_clean)
{
	while (--lines_to_clean >= 0)
		free(map->map[lines_to_clean].line);
	free(map->map);
	map->map = NULL;
	map->height = 0;
}

bool	convert_list_to_map(t_line *lst, t_map *map)
{
	int		count;
	t_line	*result;

	
	if (!validate_list_size(lst))
		return (false);
	count = ft_lstsize(lst);
	result = allocate_map_array(count);
	if (!result)
		return (false);
	if (!copy_list_to_array(lst, result))
	{
		free(result);
		return (false);
	}
	map->map = result;
	map->height = count;
	if (!find_player(map))
	{
		cleanup_map(map, count);
		return (false);
	}
	return (true);
}
