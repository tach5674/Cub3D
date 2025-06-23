/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggevorgi <sp1tak.gg@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 12:57:15 by mzohraby          #+#    #+#             */
/*   Updated: 2025/06/23 20:06:55 by ggevorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "cub3d.h"
# include "libft.h"

typedef struct s_color {
	int	r;
	int	g;
	int	b;
}	t_color;

typedef struct s_texture {
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
}	t_texture;

typedef struct s_player {
	int		x;
	int		y;
	char	dir; // 'N', 'S', 'E', 'W'
}	t_player;

typedef struct s_map {
	t_line	*map;
	int		height;
	t_player player;
}	t_map;

typedef struct s_data {
	t_texture	textures;       // пути к текстурам: NO, SO, WE, EA
	t_color		floor_color;    // F
	t_color		ceiling_color;  // C
	t_map		map;            // карта и игрок
}	t_data;

int	parse_config(int fd, t_data *data);
void	free_map(t_map *map);

#endif