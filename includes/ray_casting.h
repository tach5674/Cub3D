/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikayel <mikayel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 12:57:25 by mzohraby          #+#    #+#             */
/*   Updated: 2025/06/25 13:52:26 by mikayel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_CASTING_H
# define RAY_CASTING_H

# include "cub3d.h"

void	draw_vertical_line(t_data *data, int x, int start, int end, int color);
void	raycast(t_data *data);
#endif