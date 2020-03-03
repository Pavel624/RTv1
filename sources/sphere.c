/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsatterf <rsatterf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 21:28:51 by nbethany          #+#    #+#             */
/*   Updated: 2020/03/03 13:09:59 by rsatterf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

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

int	help_valid_sphere2(t_rtv *rtv, int i)
{
	if (data_color(rtv->scene[i + 2],
	&rtv->sphere[rtv->index[SPHERE]].prop.color, 5, rtv) != 0
	|| data_vector(rtv->scene[i + 3],
	&rtv->sphere[rtv->index[SPHERE]].center, 8, rtv) != 0)
		return (-1);
	else
		return (0);
}

int	valid_sphere(t_rtv *rtv, int i, int k)
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

int	intersect_sphere(t_sphere sphere, t_ray *ray, double *hit)
{
	double		a;
	double		b;
	double		c;
	t_vector3	distance;

	a = dot_vector3(ray->dir, ray->dir);
	if (a == 0)
		return (0);
	distance = sub_vector3(ray->origin, sphere.center);
	b = 2 * dot_vector3(distance, ray->dir);
	c = dot_vector3(distance, distance) - sphere.radius * sphere.radius;
	if (b * b - 4 * a * c < T_RAY_MIN)
		return (0);
	else
		return (calc_intersect(a, b, c, hit));
}

int	find_closest_sphere(t_ray ray, t_rtv *rtv, double *t)
{
	int	i;
	int	current;

	i = 0;
	current = -1;
	while (i < rtv->nbr[SPHERE])
	{
		if (intersect_sphere(rtv->sphere[i], &ray, t))
			current = i;
		i++;
	}
	return (current);
}
