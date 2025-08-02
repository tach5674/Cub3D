/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_handlers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzohraby <mzohraby@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 14:21:20 by mikayel           #+#    #+#             */
/*   Updated: 2025/08/02 12:28:20 by mzohraby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

#define COLLISION_RADIUS 0.2

static int	is_position_free(t_map *map, double x, double y)
{
	double	r;

	r = COLLISION_RADIUS;
	return (get_number(map, (int)(x + r), (int)(y + r)) == 0 && get_number(map,
			(int)(x - r), (int)(y + r)) == 0 && get_number(map, (int)(x + r),
			(int)(y - r)) == 0 && get_number(map, (int)(x - r), (int)(y
				- r)) == 0 && get_number(map, (int)(x + r), (int)(y)) == 0
		&& get_number(map, (int)(x - r), (int)(y)) == 0 && get_number(map,
			(int)(x), (int)(y + r)) == 0 && get_number(map, (int)(x), (int)(y
				- r)) == 0);
}

static void	move(t_data *data, double frame_time, int sign)
{
	double	move_step;
	double	new_x;
	double	new_y;

	move_step = data->move_speed * frame_time;
	new_x = data->pos_x + data->dir_x * move_step * sign;
	new_y = data->pos_y + data->dir_y * move_step * sign;
	if (is_position_free(&data->map, new_x, data->pos_y))
		data->pos_x = new_x;
	if (is_position_free(&data->map, data->pos_x, new_y))
		data->pos_y = new_y;
}

static void	straife(t_data *data, double frame_time, int sign)
{
	double	move_step;
	double	perp_x;
	double	perp_y;
	double	new_x;
	double	new_y;

	move_step = data->move_speed * frame_time;
	perp_x = data->dir_y * sign;
	perp_y = -data->dir_x * sign;
	new_x = data->pos_x + perp_x * move_step;
	new_y = data->pos_y + perp_y * move_step;
	if (is_position_free(&data->map, new_x, data->pos_y))
		data->pos_x = new_x;
	if (is_position_free(&data->map, data->pos_x, new_y))
		data->pos_y = new_y;
}

static void	rotate(t_data *data, double frame_time)
{
	double	rot_step;
	double	rot;
	double	old_dir_x;
	double	old_plane_x;

	rot_step = data->rot_speed * frame_time;
	if (data->keys.key_right && data->keys.key_right > data->keys.key_left)
		rot = rot_step;
	else
		rot = -rot_step;
	old_dir_x = data->dir_x;
	data->dir_x = data->dir_x * cos(rot) - data->dir_y * sin(rot);
	data->dir_y = old_dir_x * sin(rot) + data->dir_y * cos(rot);
	old_plane_x = data->plane_x;
	data->plane_x = data->plane_x * cos(rot) - data->plane_y * sin(rot);
	data->plane_y = old_plane_x * sin(rot) + data->plane_y * cos(rot);
}

void	handle_movement(t_data *data)
{
	struct timeval	time;
	double			current_time;
	double			frame_time;

	gettimeofday(&time, NULL);
	current_time = time.tv_sec + time.tv_usec / 1000000.0;
	frame_time = current_time - data->old_time;
	data->old_time = current_time;
	if (data->keys.key_w)
		move(data, frame_time, 1);
	if (data->keys.key_s)
		move(data, frame_time, -1);
	if (data->keys.key_d)
		straife(data, frame_time, -1);
	if (data->keys.key_a)
		straife(data, frame_time, 1);
	if (data->keys.key_left || data->keys.key_right)
		rotate(data, frame_time);
}
