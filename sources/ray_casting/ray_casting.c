/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzohraby <mzohraby@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 13:04:27 by mzohraby          #+#    #+#             */
/*   Updated: 2025/07/09 14:33:21 by mzohraby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	get_color(int map_value, int side)
{
	if (map_value == 1) return side ? 0x800000 : 0xFF0000;
	else if (map_value == 2) return side ? 0x008000 : 0x00FF00;
	else if (map_value == 3) return side ? 0x000080 : 0x0000FF;
	else if (map_value == 4) return side ? 0x808080 : 0xFFFFFF;
	else return side ? 0x808000 : 0xFFFF00;
}

void	draw_vertical_line(t_data *data, int x, int start, int end, int color)
{
	for (int y = start; y <= end; y++)
		my_mlx_pixel_put(data, x, y, color);
}

// static int get_number(t_data *data, t_line *line, int map_y, int map_x)
// {
// 	int	i;
// 	int	j;
// 	t_line *temp;
	
// 	i = 0;
// 	j = 0;
// 	temp = line;
// 	if (map_y >= data->map.height)
// 		return (-1);
// 	while (j < map_y)
// 	{
// 		temp = temp->next;
// 		j++;
// 	}
// 	if (map_x >= temp->line_length)
// 		return (-1);
// 	while (i < map_x)
// 		i++;
// 	return (temp->line[i] - '0');
// }


int	get_number(t_map *map, int map_x, int map_y)
{
	t_line *current;
	int i;

	if (!map || map_x < 0 || map_y < 0)
		return -1;

	current = map->map;
	i = 0;

	// Traverse to the desired line (map_y)
	while (current && i < map_y)
	{
		current = current->next;
		i++;
	}

	if (!current || !current->line || map_x >= current->line_length)
		return -1; // out of bounds or malformed line

	char cell = current->line[map_x];
	if (cell == ' ')
		return -2; // space = void
	else if (cell == 'N' || cell == 'S' || cell == 'E' || cell == 'W')
		return 0;
	else if (cell >= '0' && cell <= '9')
		return cell - '0';

	return -1;
}


void	raycast(t_data *data)
{
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
				hit = 1;
		}

		double perp_wall_dist = (side == 0) ? (side_dist_x - delta_dist_x) : (side_dist_y - delta_dist_y);
		int line_height = (int)(SCREEN_HEIGHT / perp_wall_dist);
		int draw_start = -line_height / 2 + SCREEN_HEIGHT / 2;
		int draw_end = line_height / 2 + SCREEN_HEIGHT / 2;
		if (draw_start < 0) draw_start = 0;
		if (draw_end >= SCREEN_HEIGHT) draw_end = SCREEN_HEIGHT - 1;

		int color = get_color(get_number(&data->map, map_x, map_y), side);
		draw_vertical_line(data, x, draw_start, draw_end, color);
	}
}
