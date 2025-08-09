/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzohraby <mzohraby@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 12:59:31 by mzohraby          #+#    #+#             */
/*   Updated: 2025/08/09 17:46:15 by mzohraby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

#define MAP_WIDTH 24
#define MAP_HEIGHT 24

// void	print_map(const t_map *map)
// {
// 	if (!map || !map->map)
// 	{
// 		printf("Map is empty or NULL\n");
// 		return ;
// 	}
// 	for (int y = 0; y < map->height; y++)
// 	{
// 		if (map->map[y].line)
// 			printf("%s\n", map->map[y].line);
// 		else
// 			printf("(null line)\n");
// 	}
// }

int	render_frame(t_data *data)
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
	// printf("FPS: %f\n", 1.0 / frame_time);
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	data;
	int		fd;

	if (argc != 2)
		return (printf("Usage: %s <map_file>\n", argv[0]), 1);
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		return (perror("Error opening file"), 1);
	if (!parse_config(fd, &data))
		return (close(fd), 1);
	close(fd);
	// print_map(&data.map);
	printf("Map parsed successfully. Player at (%d, %d) facing %c\n",
		data.map.player.x, data.map.player.y, data.map.player.dir);
	init(&data);
	free_data(&data, &data.map);
}
