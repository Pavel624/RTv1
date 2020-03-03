/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_cone.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsatterf <rsatterf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 12:00:32 by rsatterf          #+#    #+#             */
/*   Updated: 2020/03/03 13:08:08 by rsatterf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int	help_valid_cone(t_rtv *rtv, int i, int k)
{
	if ((i + 8) >= k || ft_strcmp(rtv->scene[i + 1], "{\0") != 0 ||
		ft_strcmp(rtv->scene[i + 8], "}\0") != 0 ||
		ft_strncmp(rtv->scene[i + 2], "	col(", 5) != 0 ||
		ft_strncmp(rtv->scene[i + 3], "	dir(", 5) != 0 ||
		ft_strncmp(rtv->scene[i + 4], "	center(", 8) != 0 ||
		ft_strncmp(rtv->scene[i + 5], "	angle(", 7) != 0 ||
		ft_strncmp(rtv->scene[i + 6], "	specular(", 10) != 0 ||
		ft_strncmp(rtv->scene[i + 7], "	reflection(", 12) != 0)
		return (-1);
	else
		return (0);
}

int	help_valid_cone2(t_rtv *rtv, int i)
{
	if (data_color(rtv->scene[i + 2],
		&rtv->cone[rtv->index[CONE]].prop.color, 5, rtv) != 0
	|| data_vector_norm(rtv->scene[i + 3],
		&rtv->cone[rtv->index[CONE]].dir, 5, rtv) != 0
	|| data_vector(rtv->scene[i + 4],
		&rtv->cone[rtv->index[CONE]].center, 8, rtv) != 0)
		return (-1);
	else
		return (0);
}

int	help_valid_cone3(t_rtv *rtv)
{
	if ((rtv->cone[rtv->index[CONE]].angle <= 0) ||
		(rtv->cone[rtv->index[CONE]].angle >= 90))
		return (-1);
	else
		return (0);
}

int	valid_cone(t_rtv *rtv, int i, int k)
{
	char *str;

	if (help_valid_cone(rtv, i, k) != 0)
		return (-1);
	if (help_valid_cone2(rtv, i) != 0)
		return (-1);
	str = shift_str(rtv->scene[i + 5], 7);
	if (valid_count2(str) != 0)
		return (-1);
	rtv->cone[rtv->index[CONE]].angle = ft_atoi(str);
	if (help_valid_cone3(rtv) != 0)
		return (-1);
	rtv->cone[rtv->index[CONE]].angle *= M_PI / 180;
	str = shift_str(rtv->scene[i + 6], 10);
	if (valid_count2(str) != 0)
		return (-1);
	rtv->cone[rtv->index[CONE]].prop.specular = ft_atoi(str);
	str = shift_str(rtv->scene[i + 7], 12);
	if (valid_count2(str) != 0)
		return (-1);
	rtv->cone[rtv->index[CONE]].prop.reflection = ft_atoi(str);
	if (valid_prop(&rtv->cone[rtv->index[CONE]].prop) != 0)
		return (-1);
	rtv->index[CONE]++;
	return (0);
}
