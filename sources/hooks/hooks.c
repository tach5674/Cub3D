/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikayel <mikayel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 13:35:04 by mikayel           #+#    #+#             */
/*   Updated: 2025/06/25 14:21:37 by mikayel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int key_press(int keycode, t_data *data)
{
    if (keycode == 65307) // ESC
    {
        mlx_destroy_window(data->mlx, data->win);
		// mlx_destroy_image(data->mlx, data->img);
        exit(0);
    }
    else if (keycode == 119) data->keys.key_w = 1;        // W
    else if (keycode == 115) data->keys.key_s = 1;        // S
    else if (keycode == 97) data->keys.key_a = 1;         // A
    else if (keycode == 100) data->keys.key_d = 1;        // D
    else if (keycode == 65361) data->keys.key_left = data->keys.key_right + 1;   // Left arrow
    else if (keycode == 65363) data->keys.key_right = data->keys.key_left + 1;  // Right arrow
    return (0);
}

int key_release(int keycode, t_data *data)
{
    if (keycode == 119) data->keys.key_w = 0;        // W
    else if (keycode == 115) data->keys.key_s = 0;        // S
    else if (keycode == 97) data->keys.key_a = 0;         // A
    else if (keycode == 100) data->keys.key_d = 0;        // D
    else if (keycode == 65361) data->keys.key_left = 0;   // Left arrow
    else if (keycode == 65363) data->keys.key_right = 0;  // Right arrow
    return (0);
}
