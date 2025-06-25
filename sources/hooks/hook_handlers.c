/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_handlers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikayel <mikayel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 14:21:20 by mikayel           #+#    #+#             */
/*   Updated: 2025/06/25 14:22:00 by mikayel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void    move(t_data *data, double frame_time, int sign)
{
    double  move_step;

    move_step = data->move_speed * frame_time;

    if (world_map[(int)(data->pos_y)][(int)(data->pos_x + data->dir_x * move_step * sign)] == 0)
        data->pos_x += data->dir_x * move_step * sign;
    if (world_map[(int)(data->pos_y + data->dir_y * move_step * sign)][(int)data->pos_x] == 0)
        data->pos_y += data->dir_y * move_step * sign;
}

static void    straife(t_data *data, double frame_time, int sign)
{
    double  move_step;
    double perp_x;
    double perp_y;
    
    perp_x = data->dir_y * sign;
    perp_y = -data->dir_x * sign;
    move_step = data->move_speed * frame_time;

    if (world_map[(int)(data->pos_y)][(int)(data->pos_x + perp_x * move_step)] == 0)
        data->pos_x += perp_x * move_step;
    if (world_map[(int)(data->pos_y + perp_y * move_step)][(int)data->pos_x] == 0)
        data->pos_y += perp_y * move_step;
}

static void    rotate(t_data *data, double frame_time)
{
    double rot_step;
    double rot;
    double old_dir_x;
    double old_plane_x;
    
    rot_step = data->rot_speed * frame_time;
    if (data->keys.key_right && data->keys.key_right > data->keys.key_left)
        rot = -rot_step;
    else
        rot = rot_step;
    old_dir_x = data->dir_x;
    data->dir_x = data->dir_x * cos(rot) - data->dir_y * sin(rot);
    data->dir_y = old_dir_x * sin(rot) + data->dir_y * cos(rot);
    old_plane_x = data->plane_x;
    data->plane_x = data->plane_x * cos(rot) - data->plane_y * sin(rot);
    data->plane_y = old_plane_x * sin(rot) + data->plane_y * cos(rot);
}

void handle_movement(t_data *data)
{
    struct timeval  time;
    double          current_time;
    double          frame_time;

    gettimeofday(&time, NULL);
    current_time = time.tv_sec + time.tv_usec / 1000000.0;
    frame_time = current_time - data->old_time;
    data->old_time = current_time;
    if (data->keys.key_w) // Forward
        move(data, frame_time, 1);
    if (data->keys.key_s) // Backward
        move(data, frame_time, -1);
    if (data->keys.key_d) // Strafe right
        straife(data, frame_time, 1);
    if (data->keys.key_a) // Strafe left
        straife(data, frame_time, -1);
    if (data->keys.key_left || data->keys.key_right) // Rotation
        rotate(data, frame_time);
}
