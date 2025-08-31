/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggevorgi <sp1tak.gg@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 15:07:27 by mzohraby          #+#    #+#             */
/*   Updated: 2025/08/31 17:49:05 by ggevorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	convert_textures(t_data *data, int k)
{
	unsigned char	rgb[3];
	int				i;
	int				j;
	int				offset;

	j = 0;
	while (j < TEXTURE_HEIGHT)
	{
		i = 0;
		while (i < TEXTURE_WIDTH)
		{
			offset = j * data->textures.line_len + i * (data->textures.bpp / 8);
			rgb[0] = data->textures.addr[offset + 2];
			rgb[1] = data->textures.addr[offset + 1];
			rgb[2] = data->textures.addr[offset + 0];
			data->textures_ready[k][TEXTURE_WIDTH * j
				+ i] = (rgb[0] << 16) | (rgb[1] << 8) | rgb[2];
			i++;
		}
		j++;
	}
}

static void	load_textures_helper(t_data *data, char *path, int k)
{
	data->textures.img = mlx_xpm_file_to_image(data->mlx, path,
			&data->textures.x, &data->textures.y);
	if (!data->textures.img || data->textures.x != TEXTURE_WIDTH
		|| data->textures.y != TEXTURE_HEIGHT)
	{
		printf("Error\n%s%s%s\n", "Failed to load ", path, " or wrong size.");
		close_window(data, EXIT_FAILURE);
	}
	data->textures.addr = mlx_get_data_addr(data->textures.img,
			&data->textures.bpp, &data->textures.line_len,
			&data->textures.endian);
	convert_textures(data, k);
	mlx_destroy_image(data->mlx, data->textures.img);
}

void	load_all_textures(t_data *data)
{
	load_textures_helper(data, data->textures.no, 0);
	load_textures_helper(data, data->textures.ea, 1);
	load_textures_helper(data, data->textures.so, 2);
	load_textures_helper(data, data->textures.we, 3);
}
