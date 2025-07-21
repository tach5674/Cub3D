/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzohraby <mzohraby@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 13:04:27 by mzohraby          #+#    #+#             */
/*   Updated: 2025/07/21 15:04:19 by mzohraby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

// static int	get_color(int map_value, int side)
// {
// 	if (map_value == 1) return side ? 0x800000 : 0xFF0000;
// 	else if (map_value == 2) return side ? 0x008000 : 0x00FF00;
// 	else if (map_value == 3) return side ? 0x000080 : 0x0000FF;
// 	else if (map_value == 4) return side ? 0x808080 : 0xFFFFFF;
// 	else return side ? 0x808000 : 0xFFFF00;
// }

void	draw_vertical_line(t_data *data, int x, int start, int end, int color)
{
	for (int y = start; y <= end; y++)
		my_mlx_pixel_put(data, x, y, color);
}

void	raycast(t_data *data)
{
    int floor_start = SCREEN_HEIGHT / 2;

    for (int y = floor_start; y < SCREEN_HEIGHT; y++)
    {
        for (int x = 0; x < SCREEN_WIDTH; x++)
        {
            my_mlx_pixel_put(data, x, y, create_trgb(0, data->floor_color.r, data->floor_color.g, data->floor_color.b));
            my_mlx_pixel_put(data, x, SCREEN_HEIGHT - y - 1, create_trgb(0, data->ceiling_color.r, data->ceiling_color.g, data->ceiling_color.b));
        }
    }
	for (int x = 0; x < SCREEN_WIDTH; x++)
	{
		double camera_x = 2 * x / (double)SCREEN_WIDTH - 1;
		double ray_dir_x = data->dir_x + data->plane_x * camera_x;
		double ray_dir_y = data->dir_y + data->plane_y * camera_x;

		int map_x = (int)data->pos_x;
		int map_y = (int)data->pos_y;
		double delta_dist_x = fabs(1.0 / (ray_dir_x == 0 ? 1e-6 : ray_dir_x));
		double delta_dist_y = fabs(1.0 / (ray_dir_y == 0 ? 1e-6 : ray_dir_y));

		double side_dist_x, side_dist_y;
		int step_x, step_y, hit = 0, side;

		if (ray_dir_x < 0)
		{
			step_x = -1;
			side_dist_x = (data->pos_x - map_x) * delta_dist_x;
		}
		else
		{
			step_x = 1;
			side_dist_x = (map_x + 1.0 - data->pos_x) * delta_dist_x;
		}
		if (ray_dir_y < 0)
		{
			step_y = -1;
			side_dist_y = (data->pos_y - map_y) * delta_dist_y;
		}
		else
		{
			step_y = 1;
			side_dist_y = (map_y + 1.0 - data->pos_y) * delta_dist_y;
		}

		while (!hit)
		{
			if (side_dist_x < side_dist_y)
			{
				side_dist_x += delta_dist_x;
				map_x += step_x;
				side = 0;
			}
			else
			{
				side_dist_y += delta_dist_y;
				map_y += step_y;
				side = 1;
			}
			if (map_y >= data->map.height)
			{
				printf("Unexpected hit\n");
				break;
			}
			if (get_number(&data->map, map_x, map_y) > 0)
			{
				hit = 1;
			}
		}

		double perp_wall_dist = (side == 0) ? (side_dist_x - delta_dist_x) : (side_dist_y - delta_dist_y);
		int line_height = (int)(SCREEN_HEIGHT / perp_wall_dist);
		int draw_start = -line_height / 2 + SCREEN_HEIGHT / 2;
		int draw_end = line_height / 2 + SCREEN_HEIGHT / 2;
		if (draw_start < 0) draw_start = 0;
		if (draw_end >= SCREEN_HEIGHT) draw_end = SCREEN_HEIGHT - 1;

		// int color = get_color(get_number(&data->map, map_x, map_y), side);
		// draw_vertical_line(data, x, draw_start, draw_end, color);
		
		int texture_id = get_number(&data->map, map_x, map_y) - 1;

		// Wall hit X
		double wall_x;
		if (side == 0)
			wall_x = data->pos_y + perp_wall_dist * ray_dir_y;
		else
			wall_x = data->pos_x + perp_wall_dist * ray_dir_x;
		wall_x -= floor(wall_x);

		// Texture X
		int tex_x = (int)(wall_x * (double)TEXTURE_WIDTH);
		if ((side == 0 && ray_dir_x > 0) || (side == 1 && ray_dir_y < 0))
			tex_x = TEXTURE_WIDTH - tex_x - 1;

		// Draw textured vertical line
		for (int y = draw_start; y < draw_end; y++)
		{
			int d = y * 256 - SCREEN_HEIGHT * 128 + line_height * 128;
			int tex_y = ((d * TEXTURE_HEIGHT) / line_height) / 256;
			int color = data->textures_test[texture_id][TEXTURE_HEIGHT * tex_y + tex_x];
			if (side)
				color = (color >> 1) & 0x7F7F7F;
			my_mlx_pixel_put(data, x, y, color);
		}

	}
}
