/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzohraby <mzohraby@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 15:03:04 by mzohraby          #+#    #+#             */
/*   Updated: 2025/08/17 16:58:57 by mzohraby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	choose_texture(t_data_rc *data_rc)
{
	if (data_rc->side == 0)
	{
		if (data_rc->ray_dir_x > 0)
			data_rc->texture_id = 1;
		else
			data_rc->texture_id = 3;
	}
	else
	{
		if (data_rc->ray_dir_y > 0)
			data_rc->texture_id = 2;
		else
			data_rc->texture_id = 0;
	}
}
