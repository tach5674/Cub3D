/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikayel <mikayel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 13:29:38 by mikayel           #+#    #+#             */
/*   Updated: 2025/06/25 13:48:56 by mikayel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void    init(t_data *data)
{
    struct timeval time;

    data->mlx = mlx_init();
	if (!data->mlx)
        exit(EXIT_FAILURE);
	data->win = mlx_new_window(data->mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "Raycaster");
	if (!data->win)
        exit(EXIT_FAILURE);
	ft_memset(&data->keys, 0, sizeof(t_keys));
	data->pos_x = 22;
	data->pos_y = 12;
	data->dir_x = -1;
	data->dir_y = 0;
	data->plane_x = 0;
	data->plane_y = 0.66;
	data->move_speed = 3;
	data->rot_speed = 2.5;
	// data->img = mlx_new_image(data->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	// data->addr = mlx_get_data_addr(data->img, &data->bits_per_pixel, &data->line_length, &data->endian);
    gettimeofday(&time, NULL);
    data->old_time = time.tv_sec + time.tv_usec / 1000000.0;
	mlx_hook(data->win, 2, 1L<<0, key_press, data);
    mlx_hook(data->win, 3, 1L<<1, key_release, data);
	mlx_loop_hook(data->mlx, render_frame, data);
	mlx_loop(data->mlx);
}
