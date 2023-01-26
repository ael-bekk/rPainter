/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-bekk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 14:07:57 by ael-bekk          #+#    #+#             */
/*   Updated: 2021/11/09 14:17:03 by ael-bekk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_size_nb(int n)
{
	int	i;

	i = 1 + !(n) + (n < 0);
	while (n && i++)
		n /= 10;
	return (i);
}

char	*ft_itoa(int n)
{
	char			*res;
	int				i;
	unsigned int	u;

	i = ft_size_nb(n);
	res = (char *)ft_calloc(i, 1);
	if (!res)
		return (NULL);
	res[0] = '-';
	res[--i] = '\0';
	u = -n * (n < 0) + n * !(n < 0);
	if (!u)
		res[i - 1] = '0';
	while (u)
	{
		res[--i] = (u % 10) + '0';
		u /= 10;
	}
	return (res);
}
