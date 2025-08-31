/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_custom_atoi.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggevorgi <sp1tak.gg@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/31 16:57:19 by ggevorgi          #+#    #+#             */
/*   Updated: 2025/08/31 17:49:08 by ggevorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static bool	ft_isspace(char c)
{
	return ((c >= 9 && c <= 13) || c == 32);
}

static char	*valid_number(char *str)
{
	char	*num;
	int		len;

	while (ft_isspace(*str))
		str++;
	if (*str == '+')
		str++;
	else if (*str == '-' || !ft_isdigit(*str))
		return (NULL);
	num = str;
	len = 0;
	while (ft_isdigit(*str))
	{
		len++;
		str++;
	}
	while (ft_isspace(*str))
		str++;
	if (*str != '\0')
		return (NULL);
	if (len == 0 || len > 10)
		return (NULL);
	num[len] = '\0';
	return (num);
}

int	ft_custom_atoi(char *str)
{
	int	num;

	num = 0;
	str = valid_number(str);
	if (!str)
		return (-1);
	while (*str)
		num = (num * 10) + (*str++ - '0');
	if (num > INT_MAX || num < 0)
		return (-1);
	return (num);
}