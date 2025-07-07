/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggevorgi <sp1tak.gg@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 17:14:56 by ggevorgi          #+#    #+#             */
/*   Updated: 2025/06/23 19:04:07 by ggevorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_line	*ft_lstnew(char	*data)
{
	t_line	*nnode;

	nnode = (t_line *)malloc(sizeof(t_line));
	if (!nnode)
		return (NULL);
	nnode->line = data;
	nnode->line_length = ft_strlen(data);
	nnode->next = NULL;
	return (nnode);
}
