/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation_objects.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsatterf <rsatterf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/02 14:50:46 by rsatterf          #+#    #+#             */
/*   Updated: 2020/03/02 18:02:01 by rsatterf         ###   ########.fr       */
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
	if (data_vector(rtv->scene[i + 2], &rtv->cam[rtv->index[CAM]].pos, 5) != 0
	|| data_vector_norm(str = rtv->scene[i + 3],
		&rtv->cam[rtv->index[CAM]].dir, 5) != 0)
		return (-1);
	str = shift_str(rtv->scene[i + 4], 5);
	if (valid_count2(str) != 0)
		return (-1);
	rtv->cam[rtv->index[CAM]].fov = ft_atoi(str);
	if (rtv->cam->fov < 0 || rtv->cam->fov > 360)
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
		&rtv->light[rtv->index[LIGHT]].color, 5) != 0
	|| data_vector(str = rtv->scene[i + 3],
		&rtv->light[rtv->index[LIGHT]].pos, 5) != 0)
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

int		help_valid_plane(t_rtv *rtv, int i, int k)
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

int		valid_plane(t_rtv *rtv, int i, int k)
{
	char *str;

	if (help_valid_plane(rtv, i, k) != 0)
		return (-1);
	if (data_color(rtv->scene[i + 2],
		&rtv->plane[rtv->index[PLANE]].prop.color, 5) != 0
		|| data_vector_norm(rtv->scene[i + 3],
		&rtv->plane[rtv->index[PLANE]].norm, 6) != 0)
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

int	help_valid_sphere(t_rtv *rtv, int i, int k)
{
	if ((i + 7) >= k || ft_strcmp(rtv->scene[i + 1], "{\0") != 0 ||
		ft_strcmp(rtv->scene[i + 7], "}\0") != 0 ||
		ft_strncmp(rtv->scene[i + 2], "	col(", 5) != 0 ||
		ft_strncmp(rtv->scene[i + 3], "	center(", 8) != 0 ||
		ft_strncmp(rtv->scene[i + 4], "	radius(", 8) != 0 ||
		ft_strncmp(rtv->scene[i + 5], "	specular(", 10) != 0 ||
		ft_strncmp(rtv->scene[i + 6], "	reflection(", 12) != 0)
		return (-1);
	else
		return (0);
}

int		help_valid_sphere2(t_rtv *rtv, int i)
{
	if (data_color(rtv->scene[i + 2],
	&rtv->sphere[rtv->index[SPHERE]].prop.color, 5) != 0
	|| data_vector(rtv->scene[i + 3],
	&rtv->sphere[rtv->index[SPHERE]].center, 8) != 0)
		return (-1);
	else
		return (0);
}

int		valid_sphere(t_rtv *rtv, int i, int k)
{
	char *str;

	if (help_valid_sphere(rtv, i, k) != 0)
		return (-1);
	if (help_valid_sphere2(rtv, i))
		return (-1);
	str = shift_str(rtv->scene[i + 4], 8);
	if (valid_count2(str) != 0)
		return (-1);
	rtv->sphere[rtv->index[SPHERE]].radius = ft_atoi(str);
	if (rtv->sphere[rtv->index[SPHERE]].radius < 0)
		return (-1);
	str = shift_str(rtv->scene[i + 5], 10);
	if (valid_count2(str) != 0)
		return (-1);
	rtv->sphere[rtv->index[SPHERE]].prop.specular = ft_atoi(str);
	str = shift_str(rtv->scene[i + 6], 12);
	if (valid_count2(str) != 0)
		return (-1);
	rtv->sphere[rtv->index[SPHERE]].prop.reflection = ft_atoi(str);
	if (valid_prop(&rtv->sphere[rtv->index[SPHERE]].prop) != 0)
		return (-1);
	rtv->index[SPHERE]++;
	return (0);
}

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
		&rtv->cylinder[rtv->index[CYLINDER]].prop.color, 5) != 0
	|| data_vector_norm(rtv->scene[i + 3],
		&rtv->cylinder[rtv->index[CYLINDER]].dir, 5) != 0
	|| data_vector(rtv->scene[i + 4],
		&rtv->cylinder[rtv->index[CYLINDER]].center, 8) != 0)
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

int		help_valid_cone(t_rtv *rtv, int i, int k)
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

int		help_valid_cone2(t_rtv *rtv, int i)
{
	if (data_color(rtv->scene[i + 2],
		&rtv->cone[rtv->index[CONE]].prop.color, 5) != 0
	|| data_vector_norm(rtv->scene[i + 3],
		&rtv->cone[rtv->index[CONE]].dir, 5) != 0
	|| data_vector(rtv->scene[i + 4],
		&rtv->cone[rtv->index[CONE]].center, 8) != 0)
		return (-1);
	else
		return (0);
}

int		valid_cone(t_rtv *rtv, int i, int k)
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
	if ((rtv->cone[rtv->index[CONE]].angle <= 0) ||
		(rtv->cone[rtv->index[CONE]].angle >= 90))
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
