/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzohraby <mzohraby@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 16:40:27 by mzohraby          #+#    #+#             */
/*   Updated: 2025/08/17 16:43:39 by mzohraby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	parsing_init(t_data *data)
{
	data->textures.no = NULL;
	data->textures.we = NULL;
	data->textures.ea = NULL;
	data->textures.so = NULL;
	data->ceiling_color.r = 0;
	data->ceiling_color.g = 150;
	data->ceiling_color.b = 255;
	data->floor_color.r = 150;
	data->floor_color.g = 84;
	data->floor_color.b = 47;
	data->map.map = NULL;
}
