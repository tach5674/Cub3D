/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzohraby <mzohraby@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 12:04:46 by ggevorgi          #+#    #+#             */
/*   Updated: 2025/08/17 16:39:12 by mzohraby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	ft_lstclear(t_line **lst, void (*del)(void *))
{
	t_line	*tmp;

	if (!lst || !del)
		return ;
	while (*lst)
	{
		tmp = (*lst)->next;
		del((*lst)->line);
		free(*lst);
		*lst = tmp;
	}
}

char	*trim_newline(char *line)
{
	int	len;

	len = ft_strlen(line);
	if (len > 0 && line[len - 1] == '\n')
		line[len - 1] = '\0';
	return (line);
}

void	ft_free_split(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}

void	free_data(t_data *data, t_map *map)
{
	int	i;

	get_next_line(-1);
	free(data->textures.no);
	free(data->textures.we);
	free(data->textures.ea);
	free(data->textures.so);
	if (!map || !map->map)
		return ;
	i = 0;
	while (i < map->height)
	{
		free(map->map[i].line);
		i++;
	}
	free(map->map);
	map->map = NULL;
	map->height = 0;
}

bool	error_msg(char *msg)
{
	write(2, "Error\n", 6);
	write(2, msg, ft_strlen(msg));
	write(2, "\n", 1);
	return (false);
}
