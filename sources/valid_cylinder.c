/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_cylinder.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsatterf <rsatterf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 12:02:40 by rsatterf          #+#    #+#             */
/*   Updated: 2020/03/03 13:07:41 by rsatterf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int		help_valid_cylinder(t_rtv *rtv, int i, int k)
{
	if ((i + 8) >= k || ft_strcmp(rtv->scene[i + 1], "{\0") != 0 ||
		ft_strcmp(rtv->scene[i + 8], "}\0") != 0 ||
		ft_strncmp(rtv->scene[i + 2], "	col(", 5) != 0 ||
		ft_strncmp(rtv->scene[i + 3], "	dir(", 5) != 0 ||
		ft_strncmp(rtv->scene[i + 4], "	center(", 8) != 0 ||
		ft_strncmp(rtv->scene[i + 5], "	radius(", 8) != 0 ||
		ft_strncmp(rtv->scene[i + 7], "	reflection(", 12) != 0)
		return (-1);
	else
		return (0);
}

int		help_valid_cylinder2(t_rtv *rtv, int i)
{
	if (data_color(rtv->scene[i + 2],
		&rtv->cylinder[rtv->index[CYLINDER]].prop.color, 5, rtv) != 0
	|| data_vector_norm(rtv->scene[i + 3],
		&rtv->cylinder[rtv->index[CYLINDER]].dir, 5, rtv) != 0
	|| data_vector(rtv->scene[i + 4],
		&rtv->cylinder[rtv->index[CYLINDER]].center, 8, rtv) != 0)
		return (-1);
	else
		return (0);
}

int		valid_cylinder(t_rtv *rtv, int i, int k)
{
	char *str;

	if (help_valid_cylinder(rtv, i, k) != 0)
		return (-1);
	if (help_valid_cylinder2(rtv, i) != 0)
		return (-1);
	str = shift_str(rtv->scene[i + 5], 8);
	if (valid_count2(str) != 0)
		return (-1);
	rtv->cylinder[rtv->index[CYLINDER]].radius = ft_atoi(str);
	if (rtv->cylinder[rtv->index[CYLINDER]].radius < 0)
		return (-1);
	str = shift_str(rtv->scene[i + 6], 10);
	if (valid_count2(str) != 0)
		return (-1);
	rtv->cylinder[rtv->index[CYLINDER]].prop.specular = ft_atoi(str);
	str = shift_str(rtv->scene[i + 7], 12);
	if (valid_count2(str) != 0)
		return (-1);
	rtv->cylinder[rtv->index[CYLINDER]].prop.reflection = ft_atoi(str);
	if (valid_prop(&rtv->cylinder[rtv->index[CYLINDER]].prop) != 0)
		return (-1);
	rtv->index[CYLINDER]++;
	return (0);
}
