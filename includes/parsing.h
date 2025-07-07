/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggevorgi <sp1tak.gg@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 12:57:15 by mzohraby          #+#    #+#             */
/*   Updated: 2025/07/07 12:16:32 by ggevorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "cub3d.h"
# include "libft.h"
# include "stdbool.h"

void	free_map(t_map *map);
void	ft_lstclear(t_line **lst, void (*del)(void *));
char	*trim_newline(char *line);
void	ft_free_split(char **arr);
void	free_map(t_map *map);
bool	error_msg(char *msg);
bool	load_textures(t_data *data);
bool	find_player(t_map *map);
bool	is_color_line(char *line);
int		parse_texture_line(char *line, t_data *data);
bool	is_texture_line(char *line);
int		parse_color_line(char *line, t_data *data);
bool	convert_list_to_map(t_line *lst, t_map *map);
bool	parse_config(int fd, t_data *data);
bool	validate_map(t_data *data);

#endif