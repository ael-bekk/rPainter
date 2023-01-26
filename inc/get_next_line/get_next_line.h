/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-bekk <ael-bekk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 15:20:19 by ael-bekk          #+#    #+#             */
/*   Updated: 2021/12/25 17:32:24 by ael-bekk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# define BUFFER_SIZE 1
# include <stdlib.h>
# include <unistd.h>
# include <unistd.h>
# include <limits.h>
# define TRUE 1

void	*ft_free(char **s);
char	*read_buff(int fd, char **buff);
char	*read_line(int fd, char **buff);
char	*get_next_line(int fd);

int		find_new_line(char *s);
char	*ft_gnl_strjoin(char *s1, char *s2);
char	*ft_gnl_substr(char *s, int end);
void	ft_new_buff(char **buff, int start);

#endif
