/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsatterf <rsatterf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 07:34:28 by nbethany          #+#    #+#             */
/*   Updated: 2020/03/03 13:10:00 by rsatterf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int	help_valid_plane(t_rtv *rtv, int i, int k)
{
	if ((i + 7) >= k || ft_strcmp(rtv->scene[i + 1], "{\0") != 0 ||
		ft_strcmp(rtv->scene[i + 7], "}\0") != 0 ||
		ft_strncmp(rtv->scene[i + 2], "	col(", 5) != 0 ||
		ft_strncmp(rtv->scene[i + 3], "	norm(", 6) != 0 ||
		ft_strncmp(rtv->scene[i + 4], "	point(", 7) != 0 ||
		ft_strncmp(rtv->scene[i + 5], "	specular(", 10) != 0 ||
		ft_strncmp(rtv->scene[i + 6], "	reflection(", 12) != 0)
		return (-1);
	else
		return (0);
}

int	valid_plane(t_rtv *rtv, int i, int k)
{
	char *str;

	if (help_valid_plane(rtv, i, k) != 0)
		return (-1);
	if (data_color(rtv->scene[i + 2],
		&rtv->plane[rtv->index[PLANE]].prop.color, 5, rtv) != 0
		|| data_vector_norm(rtv->scene[i + 3],
		&rtv->plane[rtv->index[PLANE]].norm, 6, rtv) != 0)
		return (-1);
	str = shift_str(rtv->scene[i + 4], 7);
	if (valid_count2(str) != 0)
		return (-1);
	rtv->plane[rtv->index[PLANE]].point = ft_atoi(str);
	str = shift_str(rtv->scene[i + 5], 10);
	if (valid_count2(str) != 0)
		return (-1);
	rtv->plane[rtv->index[PLANE]].prop.specular = ft_atoi(str);
	str = shift_str(rtv->scene[i + 6], 12);
	if (valid_count2(str) != 0)
		return (-1);
	rtv->plane[rtv->index[PLANE]].prop.reflection = ft_atoi(str);
	if (valid_prop(&rtv->plane[rtv->index[PLANE]].prop) != 0)
		return (-1);
	rtv->index[PLANE]++;
	return (0);
}

int	intersect_plane(t_plane plane, t_ray *ray, double *hit)
{
	double	dot;
	double	t1;

	dot = dot_vector3(plane.norm, ray->dir);
	if (fabs(dot) > 0.00001f)
	{
		t1 = (plane.point - dot_vector3(plane.norm, ray->origin)) / dot;
		if (t1 > 0.001f && (t1 < *hit || *hit == -1))
		{
			*hit = t1;
			return (1);
		}
		else
			return (0);
	}
	return (0);
}

int	find_closest_plane(t_ray ray, t_rtv *rtv, double *t)
{
	int i;
	int current;

	i = 0;
	current = -1;
	while (i < rtv->nbr[PLANE])
	{
		if (intersect_plane(rtv->plane[i], &ray, t))
			current = i;
		i++;
	}
	return (current);
}
