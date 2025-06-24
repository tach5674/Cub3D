/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggevorgi <sp1tak.gg@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 12:59:31 by mzohraby          #+#    #+#             */
/*   Updated: 2025/07/07 11:37:11 by ggevorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void print_map(const t_map *map)
{
    if (!map || !map->map)
    {
        printf("Map is empty or NULL\n");
        return;
    }

    for (int y = 0; y < map->height; y++)
    {
        if (map->map[y].line)
            printf("%s\n", map->map[y].line);
        else
            printf("(null line)\n");
    }
}

int main(int argc, char **argv)
{
	t_data data;
	int fd;

	if (argc != 2)
		return (printf("Usage: %s <map_file>\n", argv[0]), 1);
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		return (perror("Error opening file"), 1);
	if (!parse_config(fd, &data))
		return (close(fd), 1);
	close(fd);
	print_map(&data.map);
	// Успешно
	printf("Map parsed successfully. Player at (%d, %d) facing %c\n",
		data.map.player.x, data.map.player.y, data.map.player.dir);
	free_map(&data.map);

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 960
#define MAP_WIDTH 24
#define MAP_HEIGHT 24

int world_map[MAP_HEIGHT][MAP_WIDTH] =
{
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
	{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
	{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

int	get_color(int map_value, int side)
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
			if (world_map[map_y][map_x] > 0)
				hit = 1;
		}

		double perp_wall_dist = (side == 0) ? (side_dist_x - delta_dist_x) : (side_dist_y - delta_dist_y);
		int line_height = (int)(SCREEN_HEIGHT / perp_wall_dist);
		int draw_start = -line_height / 2 + SCREEN_HEIGHT / 2;
		int draw_end = line_height / 2 + SCREEN_HEIGHT / 2;
		if (draw_start < 0) draw_start = 0;
		if (draw_end >= SCREEN_HEIGHT) draw_end = SCREEN_HEIGHT - 1;

		int color = get_color(world_map[map_y][map_x], side);
		draw_vertical_line(data, x, draw_start, draw_end, color);
	}
}

int	key_press(int keycode, t_data *data)
{
	if (keycode == 65307) // ESC
	{
		mlx_destroy_window(data->mlx, data->win);
		exit(0);
	}
	else if (keycode == 119) // W
	{
		if (world_map[(int)(data->pos_y)][(int)(data->pos_x + data->dir_x * data->move_speed)] == 0)
			data->pos_x += data->dir_x * data->move_speed;
		if (world_map[(int)(data->pos_y + data->dir_y * data->move_speed)][(int)data->pos_x] == 0)
			data->pos_y += data->dir_y * data->move_speed;
	}
	else if (keycode == 115) // S
	{
		if (world_map[(int)(data->pos_y)][(int)(data->pos_x - data->dir_x * data->move_speed)] == 0)
			data->pos_x -= data->dir_x * data->move_speed;
		if (world_map[(int)(data->pos_y - data->dir_y * data->move_speed)][(int)data->pos_x] == 0)
			data->pos_y -= data->dir_y * data->move_speed;
	}
	else if (keycode == 100) // D (strafe right)
	{
		double perp_x = data->dir_y;
		double perp_y = -data->dir_x;
		if (world_map[(int)(data->pos_y)][(int)(data->pos_x + perp_x * data->move_speed)] == 0)
			data->pos_x += perp_x * data->move_speed;
		if (world_map[(int)(data->pos_y + perp_y * data->move_speed)][(int)data->pos_x] == 0)
			data->pos_y += perp_y * data->move_speed;
	}
	else if (keycode == 97) // A (strafe left)
	{
		double perp_x = -data->dir_y;
		double perp_y = data->dir_x;
		if (world_map[(int)(data->pos_y)][(int)(data->pos_x + perp_x * data->move_speed)] == 0)
			data->pos_x += perp_x * data->move_speed;
		if (world_map[(int)(data->pos_y + perp_y * data->move_speed)][(int)data->pos_x] == 0)
			data->pos_y += perp_y * data->move_speed;
	}
	else if (keycode == 65363 || keycode == 65361) // Right / Left arrow
	{
		double rot = (keycode == 65363) ? -data->rot_speed : data->rot_speed;
		double old_dir_x = data->dir_x;
		data->dir_x = data->dir_x * cos(rot) - data->dir_y * sin(rot);
		data->dir_y = old_dir_x * sin(rot) + data->dir_y * cos(rot);
		double old_plane_x = data->plane_x;
		data->plane_x = data->plane_x * cos(rot) - data->plane_y * sin(rot);
		data->plane_y = old_plane_x * sin(rot) + data->plane_y * cos(rot);
	}
	return (0);
}

int	render_frame(t_data *data)
{
	struct timeval	time;
	double	frame_time;

	gettimeofday(&time, NULL);
	frame_time = time.tv_sec + time.tv_usec / 1000000.0;

	data->img = mlx_new_image(data->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	data->addr = mlx_get_data_addr(data->img, &data->bits_per_pixel, &data->line_length, &data->endian);

	data->move_speed = 0.05;
	data->rot_speed = 0.05;

	raycast(data);
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
	mlx_destroy_image(data->mlx, data->img);

	gettimeofday(&time, NULL);
	frame_time = time.tv_sec + time.tv_usec / 1000000.0 - frame_time;
	printf("FPS: %f\n", 1.0 / frame_time);
	return (0);
}

int	main(int argc, char *argv[])
{
	t_data	data;

	parse(argc, argv);
	data.mlx = mlx_init();
	if (!data.mlx) return (1);
	data.win = mlx_new_window(data.mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "Raycaster");
	if (!data.win) return (1);

	data.pos_x = 22;
	data.pos_y = 12;
	data.dir_x = -1;
	data.dir_y = 0;
	data.plane_x = 0;
	data.plane_y = 0.66;

	mlx_hook(data.win, 2, 1L << 0, key_press, &data);
	mlx_loop_hook(data.mlx, render_frame, &data);
	mlx_loop(data.mlx);
	return (0);
}


// int	main(int argc, char *argv[])
// {
// 	void	*mlx;
// 	void	*win;

// 	parse(argc, argv);
// 	mlx = mlx_init();
// 	win = mlx_new_window(mlx, WIDTH, HEIGHT, "cub3d");
// 	mlx_loop(mlx);
// 	return (0);
// }
