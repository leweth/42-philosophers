/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atou32.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mben-yah <mben-yah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 15:46:11 by mben-yah          #+#    #+#             */
/*   Updated: 2024/08/08 18:08:21 by mben-yah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static bool	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (true);
	return (false);
}

static bool	ft_isspace(char c)
{
	if ((c >= 9 && c <= 13) || c == 32)
		return (true);
	return (false);
}

u_int32_t	ft_atou32(char *str, int16_t *err)
{
	u_int64_t	conv;
	u_int32_t	i;

	conv = 0;
	i = 0;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '+')
		i++;
	if (!ft_isdigit(str[i]))
		return (*err = INVALID_NUMBER_FORMAT, *err);
	while (ft_isdigit(str[i]))
	{
		conv = conv * 10 + str[i++] - '0';
		if (conv > UINT32_MAX)
			return (*err = NUMBER_LIMIT_EXCEEDED, *err);
	}
	if (!ft_isdigit(str[i]) && str[i])
		return (*err = INVALID_NUMBER_FORMAT, *err);
	return (conv);
}

