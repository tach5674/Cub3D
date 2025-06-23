/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggevorgi <sp1tak.gg@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 12:59:31 by mzohraby          #+#    #+#             */
/*   Updated: 2025/06/23 20:26:28 by ggevorgi         ###   ########.fr       */
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
	{
		printf("Usage: %s <map_file>\n", argv[0]);
		return (1);
	}
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
	{
		perror("Error opening file");
		return (1);
	}
	if (parse_config(fd, &data) == -1)
	{
		close(fd);
		return (1);
	}
	close(fd);
	print_map(&data.map);
	// Успешно
	printf("Map parsed successfully. Player at (%d, %d) facing %c\n",
		data.map.player.x, data.map.player.y, data.map.player.dir);
	free_map(&data.map);
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
