/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-bekk <ael-bekk@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 13:16:46 by ael-bekk          #+#    #+#             */
/*   Updated: 2023/01/22 13:30:46 by ael-bekk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>


void	*ft_free(char **s)
{
	free(*s);
	*s = NULL;
	return (NULL);
}

char	*read_buff(int fd, char **buff)
{
	int		end;
	int		bol;
	char	*res;

	bol = TRUE;
	while (bol)
	{
		res = (char *)malloc(BUFFER_SIZE + 1);
		if (!res)
			return (ft_free(buff));
		end = read(fd, res, BUFFER_SIZE);
		if (!end || end == -1)
			return (ft_free(&res));
		res[end] = 0;
		bol = (find_new_line(res) == -1);
		*buff = ft_gnl_strjoin(*buff, res);
		res = NULL;
	}
	return (*buff);
}

char	*read_line(int fd, char **buff)
{
	int		end;
	char	*line;

	line = NULL;
	end = find_new_line(*buff);
	if (end == -1)
	{
		read_buff(fd, buff);
		end = find_new_line(*buff);
	}
	if (end != -1)
	{
		line = ft_gnl_substr(*buff, end);
		ft_new_buff(buff, end + 1);
		return (line);
	}
	line = ft_gnl_strjoin(line, *buff);
	if (!line)
		ft_free(buff);
	*buff = NULL;
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*buff;
	char		*line;

	line = NULL;
	if (fd >= 0 && fd < 1200 && BUFFER_SIZE > 0)
	{
		if (!buff)
			read_buff(fd, &buff);
		if (buff)
			line = read_line(fd, &buff);
		if (!line)
			ft_free(&buff);
	}
	if (line && strlen(line) && line[strlen(line) - 1] == '\n')
		line[strlen(line) - 1] = 0;
	return (line);
}
