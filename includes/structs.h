/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzohraby <mzohraby@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 14:47:36 by mikayel           #+#    #+#             */
/*   Updated: 2025/08/02 13:05:15 by mzohraby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include "cub3d.h"

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
	int		bpp;
	int		line_len;
	int		endian;
	int		x;
	int		y;
	void	*img;
	char	*addr;
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

typedef struct	s_keys
{
    int key_w;
    int key_a;
    int key_s;
    int key_d;
    int key_left;
    int key_right;
}	t_keys;

typedef struct s_data_rc
{
	double	camera_x;
	double	ray_dir_x;
	double	ray_dir_y;
	int		map_x;
	int		map_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	perp_wall_dist;
	int		line_height;
	int		draw_start;
	int		draw_end;
	int		texture_id;
	double	wall_x;
	int		tex_x;
	int		d;
	int		tex_y;
	int		color;
	double	side_dist_x;
	double	side_dist_y;
	int		step_x;
	int		step_y;
	int		hit;
	int		side;
}	t_data_rc;

typedef struct s_data
{
	void	*mlx;
	void	*win;
	void	*img;
	char	*addr;
	int		bpp;
	int		line_length;
	int		endian;
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
	double	move_speed;
	double	rot_speed;
	double  old_time;
    t_keys	keys;
	t_texture	textures;       // пути к текстурам: NO, SO, WE, EA
	t_color		floor_color;    // F
	t_color		ceiling_color;  // C
	t_map		map;            // карта и игрок
	int 		textures_test[NUM_TEXTURES][TEXTURE_WIDTH * TEXTURE_HEIGHT];
	t_data_rc	data_rc;
}	t_data;

#endif
