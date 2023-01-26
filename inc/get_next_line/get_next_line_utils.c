/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-bekk <ael-bekk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 14:44:58 by ael-bekk          #+#    #+#             */
/*   Updated: 2021/12/22 19:56:45 by ael-bekk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	find_new_line(char *s)
{
	int	i;

	i = -1;
	while (s[++i])
		if (s[i] == '\n')
			return (i);
	return (-1);
}

char	*ft_gnl_strjoin(char *s1, char *s2)
{
	int		i;
	int		l1;
	int		l2;
	char	*res;

	l1 = 0;
	l2 = 0;
	while (s1 && s1[l1])
		l1++;
	while (s2 && s2[l2])
		l2++;
	if (!(l1 + l2))
		return (NULL);
	res = (char *)malloc(l1 + l2 + 1);
	if (!res)
		return (ft_free(&s1));
	i = -1;
	while (++i < l1)
		res[i] = s1[i];
	i = -1;
	while (++i < l2)
		res[i + l1] = s2[i];
	res[l1 + l2] = 0;
	(ft_free(&s1) || ft_free(&s2));
	return (res);
}

char	*ft_gnl_substr(char *s, int end)
{
	char	*sub;
	int		i;

	if (!s[0])
		return (ft_free(&s));
	i = -1;
	sub = (char *)malloc(end + 2);
	if (!sub)
		return (ft_free(&s));
	while (++i <= end)
		sub[i] = s[i];
	sub[end + 1] = 0;
	return (sub);
}

void	ft_new_buff(char **buff, int start)
{
	char	*new;
	int		end;

	end = 0;
	while ((*buff)[end + start])
		end++;
	if (!end)
	{
		ft_free(buff);
		return ;
	}
	new = ft_gnl_substr((*buff) + start, end - 1);
	ft_free(buff);
	*buff = new;
}
