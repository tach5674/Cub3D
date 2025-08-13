/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzohraby <mzohraby@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 13:35:04 by mikayel           #+#    #+#             */
/*   Updated: 2025/08/13 14:56:26 by mzohraby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	close_window(t_data *data)
{
	mlx_clear_window(data->mlx, data->win);
	mlx_destroy_window(data->mlx, data->win);
	mlx_destroy_image(data->mlx, data->img);
	mlx_destroy_display(data->mlx);
	free(data->mlx);
	free_data(data, &data->map);
	exit(0);
}

int	key_press(int keycode, t_data *data)
{
	if (keycode == 65307)
		close_window(data);
	else if (keycode == 119)
		data->keys.key_w = 1;
	else if (keycode == 115)
		data->keys.key_s = 1;
	else if (keycode == 97)
		data->keys.key_a = 1;
	else if (keycode == 100)
		data->keys.key_d = 1;
	else if (keycode == 65361)
		data->keys.key_left = data->keys.key_right + 1;
	else if (keycode == 65363)
		data->keys.key_right = data->keys.key_left + 1;
	return (0);
}

int	key_release(int keycode, t_data *data)
{
	if (keycode == 119)
		data->keys.key_w = 0;
	else if (keycode == 115)
		data->keys.key_s = 0;
	else if (keycode == 97)
		data->keys.key_a = 0;
	else if (keycode == 100)
		data->keys.key_d = 0;
	else if (keycode == 65361)
		data->keys.key_left = 0;
	else if (keycode == 65363)
		data->keys.key_right = 0;
	return (0);
}
