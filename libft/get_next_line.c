/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsatterf <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/10 14:57:09 by rsatterf          #+#    #+#             */
/*   Updated: 2019/01/31 18:56:43 by rsatterf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*one(char **s, int ret, char *buf, int fd)
{
	char *k;

	if (s[fd] == NULL)
		s[fd] = ft_strnew(1);
	buf[ret] = '\0';
	k = ft_strjoin(s[fd], buf);
	free(s[fd]);
	s[fd] = k;
	return (s[fd]);
}

char	*two(char **s, char **line, int fd)
{
	int		i;
	char	*k;

	i = 0;
	while ((s[fd][i] != '\n') && (s[fd][i] != '\0'))
		i++;
	*line = ft_strsub(s[fd], 0, i);
	k = ft_strdup(s[fd] + i + 1);
	free(s[fd]);
	s[fd] = k;
	return (s[fd]);
}

char	*get_line(char **s, char **line, int fd)
{
	int		i;
	char	*k;

	i = 0;
	while ((s[fd][i] != '\n') && (s[fd][i] != '\0'))
		i++;
	if (s[fd][i] == '\n')
	{
		*line = ft_strsub(s[fd], 0, i);
		k = ft_strdup(s[fd] + i + 1);
		free(s[fd]);
		s[fd] = k;
	}
	else if ((s[fd][i] == '\0') && (i != 0))
	{
		*line = ft_strsub(s[fd], 0, i);
		ft_strdel(&s[fd]);
	}
	return (s[fd]);
}

int		get_next_line(const int fd, char **line)
{
	int			ret;
	char		buf[BUFF_SIZE + 1];
	static char *s[255];

	if ((fd == -1) || (line == NULL))
		return (-1);
	while ((ret = read(fd, buf, BUFF_SIZE)) > 0)
	{
		s[fd] = one(s, ret, buf, fd);
		if (ft_strchr(buf, '\n'))
			break ;
	}
	if (ret < 0)
		return (-1);
	else if (ret == 0)
	{
		if ((s[fd] == NULL) || (s[fd][0] == '\0'))
			return (0);
		else
			s[fd] = get_line(s, line, fd);
	}
	else
		s[fd] = two(s, line, fd);
	return (1);
}

