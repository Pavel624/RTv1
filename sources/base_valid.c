/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base_valid.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsatterf <rsatterf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 12:46:21 by rsatterf          #+#    #+#             */
/*   Updated: 2020/03/03 12:48:48 by rsatterf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int		valid1(t_rtv *rtv)
{
	char *line;

	rtv->fd = open(rtv->name, O_RDONLY);
	if (rtv->fd < 0)
	{
		close(rtv->fd);
		return (-1);
	}
	if ((get_next_line(rtv->fd, &line) <= 0))
	{
		close(rtv->fd);
		return (-1);
	}
	else
	{
		ft_strdel(&line);
		close(rtv->fd);
		return (0);
	}
}

int		help_valid2(char k, t_rtv *rtv)
{
	if (((k >= 48) && (k <= 57)) || (k == ' ') || (k == '\n') ||
		(k == '-') || (k == '\t') || ((k >= 97) && (k <= 122)) ||
		(k == ')') || (k == '(') || (k == '{') || (k == '}') || (k == '_'))
	{
		rtv->i++;
		return (0);
	}
	else
		return (-1);
}

int		valid2(t_rtv *rtv)
{
	char *line;

	rtv->fd = open(rtv->name, O_RDONLY);
	while (get_next_line(rtv->fd, &line) > 0)
	{
		rtv->i = 0;
		while (line[rtv->i])
		{
			if (help_valid2(line[rtv->i], rtv) != 0)
			{
				ft_strdel(&line);
				return (-1);
			}
		}
		ft_strdel(&line);
	}
	ft_strdel(&line);
	close(rtv->fd);
	return (0);
}

int		init_k(t_rtv *rtv)
{
	int i;

	i = 0;
	while (rtv->scene[i] != NULL)
		i++;
	return (i);
}

int		valid_objects(t_rtv *rtv)
{
	int		k;

	k = init_k(rtv);
	rtv->i = 0;
	while (rtv->i < k)
	{
		if ((ft_strcmp(rtv->scene[rtv->i], "camera\0") == 0 &&
			valid_camera(rtv, rtv->i, k) == 0) ||
			(ft_strcmp(rtv->scene[rtv->i], "light\0") == 0 &&
			valid_light(rtv, rtv->i, k) == 0))
			rtv->i = rtv->i + 6;
		else if ((ft_strcmp(rtv->scene[rtv->i], "plane\0") == 0 &&
			valid_plane(rtv, rtv->i, k) == 0) ||
			(ft_strcmp(rtv->scene[rtv->i], "sphere\0") == 0 &&
			valid_sphere(rtv, rtv->i, k) == 0))
			rtv->i = rtv->i + 8;
		else if ((ft_strcmp(rtv->scene[rtv->i], "cylinder\0") == 0 &&
			valid_cylinder(rtv, rtv->i, k) == 0) ||
			(ft_strcmp(rtv->scene[rtv->i], "cone\0") == 0 &&
			valid_cone(rtv, rtv->i, k) == 0))
			rtv->i = rtv->i + 9;
		else
			return (-1);
	}
	return (0);
}
