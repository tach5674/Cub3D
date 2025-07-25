/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzohraby <mzohraby@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 13:35:19 by mikayel           #+#    #+#             */
/*   Updated: 2025/07/25 13:12:57 by mzohraby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HOOKS_H
# define HOOKS_H

# include "cub3d.h"

int     key_press(int keycode, t_data *data);
int     key_release(int keycode, t_data *data);
void    handle_movement(t_data *data);
int     close_window(t_data *data);

#endif