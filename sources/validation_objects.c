/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation_objects.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsatterf <rsatterf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/02 14:50:46 by rsatterf          #+#    #+#             */
/*   Updated: 2020/03/03 13:08:39 by rsatterf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

char	*shift_str(char *str, int k)
{
	int j;

	j = 0;
	while (j != k)
	{
		str++;
		j++;
	}
	return (str);
}

int		valid_camera(t_rtv *rtv, int i, int k)
{
	char *str;

	if ((i + 5) >= k || ft_strcmp(rtv->scene[i + 1], "{\0") != 0 ||
		ft_strcmp(rtv->scene[i + 5], "}\0") != 0 ||
		ft_strncmp(rtv->scene[i + 2], "	pos(", 5) != 0 ||
		ft_strncmp(rtv->scene[i + 3], "	dir(", 5) != 0 ||
		ft_strncmp(rtv->scene[i + 4], "	fov(", 5) != 0)
		return (-1);
	if (data_vector(rtv->scene[i + 2],
		&rtv->cam[rtv->index[CAM]].pos, 5, rtv) != 0
	|| data_vector_norm(rtv->scene[i + 3],
		&rtv->cam[rtv->index[CAM]].dir, 5, rtv) != 0)
		return (-1);
	str = shift_str(rtv->scene[i + 4], 5);
	if (valid_count2(str) != 0)
		return (-1);
	rtv->cam[rtv->index[CAM]].fov = ft_atoi(str);
	if (rtv->cam->fov < 1 || rtv->cam->fov > 180)
		return (-1);
	return (0);
}

int		valid_light(t_rtv *rtv, int i, int k)
{
	char *str;

	if ((i + 5) >= k || ft_strcmp(rtv->scene[i + 1], "{\0") != 0 ||
		ft_strcmp(rtv->scene[i + 5], "}\0") != 0 ||
		ft_strncmp(rtv->scene[i + 2], "	col(", 5) != 0 ||
		ft_strncmp(rtv->scene[i + 3], "	pos(", 5) != 0 ||
		ft_strncmp(rtv->scene[i + 4], "	bright(", 8) != 0)
		return (-1);
	if (data_color(rtv->scene[i + 2],
		&rtv->light[rtv->index[LIGHT]].color, 5, rtv) != 0
	|| data_vector(rtv->scene[i + 3],
		&rtv->light[rtv->index[LIGHT]].pos, 5, rtv) != 0)
		return (-1);
	str = shift_str(rtv->scene[i + 4], 8);
	if (valid_count2(str) != 0)
		return (-1);
	rtv->light[rtv->index[LIGHT]].brightness = ft_atoi(str);
	if ((rtv->light[rtv->index[LIGHT]].brightness < 0) ||
	(rtv->light[rtv->index[LIGHT]].brightness > 1000))
		return (-1);
	rtv->index[LIGHT]++;
	return (0);
}
