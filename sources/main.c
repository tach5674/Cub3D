/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggevorgi <sp1tak.gg@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 12:59:31 by mzohraby          #+#    #+#             */
/*   Updated: 2025/08/31 18:29:04 by ggevorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

int	main(int argc, char **argv)
{
	t_data	data;
	int		fd;

	if (argc != 2)
		return (printf("Error\nUsage: %s <map_file.cub>\n", argv[0]), 1);
	if (ft_strcmp(argv[1] + (ft_strlen(argv[1]) - 4), ".cub"))
		return (printf("Error\nUsage: %s <map_file.cub>\n", argv[0]), 1);
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		return (perror("Error\nError opening file"), 1);
	if (!parse_config(fd, &data))
	{
		free_data(&data, &data.map);
		return (close(fd), 1);
	}
	close(fd);
	printf("Map parsed successfully. Player at (%d, %d) facing %c\n",
		data.map.player.x, data.map.player.y, data.map.player.dir);
	init(&data);
	free_data(&data, &data.map);
}
