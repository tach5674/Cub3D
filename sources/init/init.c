/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzohraby <mzohraby@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 13:29:38 by mikayel           #+#    #+#             */
/*   Updated: 2025/08/13 19:51:48 by mzohraby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

static int	render_frame(t_data *data)
{
	struct timeval	time;
	double			frame_time;

	gettimeofday(&time, NULL);
	frame_time = time.tv_sec + time.tv_usec / 1000000.0;
	handle_movement(data);
	raycast(data);
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
	gettimeofday(&time, NULL);
	frame_time = time.tv_sec + time.tv_usec / 1000000.0 - frame_time;
	return (0);
}

static void	window_init(t_data *data, struct timeval *time)
{
	data->img = mlx_new_image(data->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	data->addr = mlx_get_data_addr(data->img, &data->bpp,
			&data->line_length, &data->endian);
	load_all_textures(data);
	gettimeofday(time, NULL);
	data->old_time = time->tv_sec + time->tv_usec / 1000000.0;
	mlx_hook(data->win, 17, 0, close_window, data);
	mlx_hook(data->win, 2, 1L << 0, key_press, data);
	mlx_hook(data->win, 3, 1L << 1, key_release, data);
	mlx_loop_hook(data->mlx, render_frame, data);
	mlx_loop(data->mlx);
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
	window_init(data, &time);
}
