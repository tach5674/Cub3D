/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggevorgi <sp1tak.gg@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 20:17:41 by ggevorgi          #+#    #+#             */
/*   Updated: 2025/06/23 19:07:08 by ggevorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_line	*ft_lstlast(t_line *lst)
{
	t_line	*lstcpy;

	if (!lst)
		return (NULL);
	lstcpy = lst;
	while (lstcpy->next)
	{
		lstcpy = lstcpy->next;
	}
	return (lstcpy);
}
