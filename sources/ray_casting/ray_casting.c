/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzohraby <mzohraby@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 13:04:27 by mzohraby          #+#    #+#             */
/*   Updated: 2025/08/13 18:26:48 by mzohraby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	draw_line_helper(t_data *data, t_data_rc *data_rc, int x)
{
	int	y;

	y = data_rc->draw_start;
	while (y < data_rc->draw_end)
	{
		data_rc->d = y * 256 - SCREEN_HEIGHT * 128 + data_rc->line_height * 128;
		data_rc->tex_y = ((data_rc->d * TEXTURE_HEIGHT) / data_rc->line_height)
			/ 256;
		choose_texture(data_rc);
		data_rc->color = data->textures_ready[data_rc->texture_id]
		[TEXTURE_HEIGHT * data_rc->tex_y + data_rc->tex_x];
		my_mlx_pixel_put(data, x, y, data_rc->color);
		y++;
	}
	y = -1;
	while (++y < data_rc->draw_start)
		my_mlx_pixel_put(data, x, y, create_trgb(0, data->ceiling_color.r,
				data->ceiling_color.g, data->ceiling_color.b));
	y = data_rc->draw_end - 1;
	while (++y < SCREEN_HEIGHT)
		my_mlx_pixel_put(data, x, y, create_trgb(0, data->floor_color.r,
				data->floor_color.g, data->floor_color.b));
}

static void	draw_line(t_data *data, t_data_rc *data_rc, int x)
{
	if (data_rc->side == 0)
		data_rc->pwd = data_rc->side_dist_x - data_rc->delta_dist_x;
	else
		data_rc->pwd = data_rc->side_dist_y - data_rc->delta_dist_y;
	data_rc->line_height = (int)(SCREEN_HEIGHT / data_rc->pwd);
	data_rc->draw_start = -data_rc->line_height / 2 + SCREEN_HEIGHT / 2;
	data_rc->draw_end = data_rc->line_height / 2 + SCREEN_HEIGHT / 2;
	if (data_rc->draw_start < 0)
		data_rc->draw_start = 0;
	if (data_rc->draw_end >= SCREEN_HEIGHT)
		data_rc->draw_end = SCREEN_HEIGHT - 1;
	if (data_rc->side == 0)
		data_rc->wall_x = data->pos_y + data_rc->pwd * data_rc->ray_dir_y;
	else
		data_rc->wall_x = data->pos_x + data_rc->pwd * data_rc->ray_dir_x;
	data_rc->wall_x -= floor(data_rc->wall_x);
	data_rc->tex_x = (int)(data_rc->wall_x * (double)TEXTURE_WIDTH);
	if ((data_rc->side == 0 && data_rc->ray_dir_x > 0) || (data_rc->side == 1
			&& data_rc->ray_dir_y < 0))
		data_rc->tex_x = TEXTURE_WIDTH - data_rc->tex_x - 1;
	draw_line_helper(data, data_rc, x);
}

static void	check_if_hit(t_data *data, t_data_rc *data_rc)
{
	data_rc->hit = 0;
	while (!data_rc->hit)
	{
		if (data_rc->side_dist_x < data_rc->side_dist_y)
		{
			data_rc->side_dist_x += data_rc->delta_dist_x;
			data_rc->map_x += data_rc->step_x;
			data_rc->side = 0;
		}
		else
		{
			data_rc->side_dist_y += data_rc->delta_dist_y;
			data_rc->map_y += data_rc->step_y;
			data_rc->side = 1;
		}
		if (get_number(&data->map, data_rc->map_x, data_rc->map_y) > 0)
			data_rc->hit = 1;
	}
}

static void	calculate_step(t_data *data, t_data_rc *data_rc)
{
	if (data_rc->ray_dir_x < 0)
	{
		data_rc->step_x = -1;
		data_rc->side_dist_x = (data->pos_x - data_rc->map_x)
			* data_rc->delta_dist_x;
	}
	else
	{
		data_rc->step_x = 1;
		data_rc->side_dist_x = (data_rc->map_x + 1.0 - data->pos_x)
			* data_rc->delta_dist_x;
	}
	if (data_rc->ray_dir_y < 0)
	{
		data_rc->step_y = -1;
		data_rc->side_dist_y = (data->pos_y - data_rc->map_y)
			* data_rc->delta_dist_y;
	}
	else
	{
		data_rc->step_y = 1;
		data_rc->side_dist_y = (data_rc->map_y + 1.0 - data->pos_y)
			* data_rc->delta_dist_y;
	}
}

void	raycast(t_data *data)
{
	t_data_rc	data_rc;
	int			x;

	x = 0;
	while (x < SCREEN_WIDTH)
	{
		data_rc.camera_x = 2 * x / (double)SCREEN_WIDTH - 1;
		data_rc.ray_dir_x = data->dir_x + data->plane_x * data_rc.camera_x;
		data_rc.ray_dir_y = data->dir_y + data->plane_y * data_rc.camera_x;
		data_rc.map_x = (int)data->pos_x;
		data_rc.map_y = (int)data->pos_y;
		if (data_rc.ray_dir_x == 0)
			data_rc.delta_dist_x = 1.0 / fabs(1e-6);
		else
			data_rc.delta_dist_x = 1.0 / fabs(data_rc.ray_dir_x);
		if (data_rc.ray_dir_y == 0)
			data_rc.delta_dist_y = 1.0 / fabs(1e-6);
		else
			data_rc.delta_dist_y = 1.0 / fabs(data_rc.ray_dir_y);
		calculate_step(data, &data_rc);
		check_if_hit(data, &data_rc);
		draw_line(data, &data_rc, x);
		x++;
	}
}
