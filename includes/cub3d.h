/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggevorgi <sp1tak.gg@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 12:57:01 by mzohraby          #+#    #+#             */
/*   Updated: 2025/07/02 12:12:54 by ggevorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libft.h"
# include "mlx.h"
# include "structs.h"
# include "parsing.h"
# include "libft.h"
# include "ray_casting.h"
# include "utils.h"
# include "mlx_utils.h"
# include "init.h"
# include "hooks.h"

# include <fcntl.h>    // open
# include <stdio.h>    // printf, perror
# include <stdlib.h>   // malloc, free, exit
# include <string.h>   // strerror
# include <sys/time.h> // gettimeofday
# include <unistd.h>   // close, read, write
# include <stdbool.h>	// boolean
# include <math.h>

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 960
#define MAP_WIDTH 24
#define MAP_HEIGHT 24

extern int world_map[MAP_HEIGHT][MAP_WIDTH];

int	render_frame(t_data *data);

#endif