/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-bekk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 13:55:10 by ael-bekk          #+#    #+#             */
/*   Updated: 2021/11/09 16:22:39 by ael-bekk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	*words(char const *s, char c, int *j)
{
	int	*tab;
	int	i;

	tab = (int *)ft_calloc((ft_strlen(s) / 2 + 1), sizeof(int));
	if (!tab)
		return (NULL);
	i = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			while (s[i] && s[i] != c)
			{
				tab[*j]++;
				i++;
			}
			tab[*j]++;
			(*j)++;
		}
		else
			i++;
	}
	return (tab);
}

static char	**ft_fill(char const *s, char **splt, char c, int *w)
{
	int		j;

	j = 0;
	while (*s)
	{
		if (*s != c)
		{
			splt[j] = (char *)ft_calloc(w[j], sizeof(char));
			if (!splt[j])
				return (NULL);
			ft_strlcat(splt[j], s, w[j]);
			s = s + w[j++] - 1;
		}
		else
			s++;
	}
	return (splt);
}

char	**ft_split(char const *s, char c)
{
	char	**splt;
	int		*w;
	int		j;

	j = 0;
	splt = NULL;
	if (!s)
		return (NULL);
	w = words(s, c, &j);
	if (!w)
		return (NULL);
	splt = (char **)ft_calloc((j + 1), sizeof(char *));
	if (!splt)
		return (NULL);
	splt = ft_fill(s, splt, c, w);
	free(w);
	return (splt);
}
