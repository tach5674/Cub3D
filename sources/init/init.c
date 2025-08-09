/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzohraby <mzohraby@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 13:29:38 by mikayel           #+#    #+#             */
/*   Updated: 2025/08/09 18:13:02 by mzohraby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	convert_textures(t_data *data, int k)
{
	unsigned char	rgb[3];
	int				i;
	int				j;
	int				offset;

	j = 0;
	while (j < TEXTURE_HEIGHT)
	{
		i = 0;
		while (i < TEXTURE_WIDTH)
		{
			offset = j * data->textures.line_len + i * (data->textures.bpp / 8);
			rgb[0] = data->textures.addr[offset + 2];
			rgb[1] = data->textures.addr[offset + 1];
			rgb[2] = data->textures.addr[offset + 0];
			data->textures_test[k][TEXTURE_WIDTH * j
				+ i] = (rgb[0] << 16) | (rgb[1] << 8) | rgb[2];
			i++;
		}
		j++;
	}
}

static void	load_textures_helper(t_data *data, char *path, int k)
{
	data->textures.img = mlx_xpm_file_to_image(data->mlx, path,
			&data->textures.x, &data->textures.y);
	if (!data->textures.img || data->textures.x != TEXTURE_WIDTH
		|| data->textures.y != TEXTURE_HEIGHT)
	{
		printf("Failed to load wall.xpm or wrong size.\n");
		exit(1);
	}
	data->textures.addr = mlx_get_data_addr(data->textures.img,
			&data->textures.bpp, &data->textures.line_len,
			&data->textures.endian);
	convert_textures(data, k);
	mlx_destroy_image(data->mlx, data->textures.img);
}

void	load_all_textures(t_data *data)
{
	load_textures_helper(data, data->textures.no, 0);
	load_textures_helper(data, data->textures.ea, 1);
	load_textures_helper(data, data->textures.so, 2);
	load_textures_helper(data, data->textures.we, 3);
}

static void	set_dir(t_data *data)
{
	if (data->map.player.dir == 'E')
	{
		data->dir_x = 1;
		data->dir_y = 0;
		data->plane_x = 0;
		data->plane_y = 0.66;
	}
	else if (data->map.player.dir == 'S')
	{
		data->dir_x = 0;
		data->dir_y = 1;
		data->plane_x = -0.66;
		data->plane_y = 0;
	}
	else if (data->map.player.dir == 'W')
	{
		data->dir_x = -1;
		data->dir_y = 0;
		data->plane_x = 0;
		data->plane_y = -0.66;
	}
}

void	init(t_data *data)
{
	struct timeval	time;

	data->mlx = mlx_init();
	if (!data->mlx)
		exit(EXIT_FAILURE);
	data->win = mlx_new_window(data->mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "cub3D");
	if (!data->win)
		exit(EXIT_FAILURE);
	ft_memset(&data->keys, 0, sizeof(t_keys));
	data->pos_x = data->map.player.x + 0.5;
	data->pos_y = data->map.player.y + 0.5;
	data->map.map[data->map.player.y].line[data->map.player.x] = '0';
	data->dir_x = 0;
	data->dir_y = -1;
	data->plane_x = 0.66;
	data->plane_y = 0;
	set_dir(data);
	data->move_speed = 3;
	data->rot_speed = 2.5;
	data->img = mlx_new_image(data->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	data->addr = mlx_get_data_addr(data->img, &data->bpp,
			&data->line_length, &data->endian);
	load_all_textures(data);
	gettimeofday(&time, NULL);
	data->old_time = time.tv_sec + time.tv_usec / 1000000.0;
	mlx_hook(data->win, 17, 0, close_window, data);
	mlx_hook(data->win, 2, 1L << 0, key_press, data);
	mlx_hook(data->win, 3, 1L << 1, key_release, data);
	mlx_loop_hook(data->mlx, render_frame, data);
	mlx_loop(data->mlx);
}
