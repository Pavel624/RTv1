/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbethany <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/08 19:14:09 by nbethany          #+#    #+#             */
/*   Updated: 2020/01/08 19:14:12 by nbethany         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int			intersect_cone(t_cone cone, t_ray *ray, double *hit)
{
	t_vector3	distance;
	double		k1;
	double		a;
	double		b;
	double		c;

	k1 = tan(cone.angle);
	distance = sub_vector3(ray->origin, cone.center);
	a = dot_vector3(ray->dir, ray->dir) - (1 + k1 * k1)
			* dot_vector3(ray->dir, cone.dir) * dot_vector3(ray->dir, cone.dir);
	b = (dot_vector3(ray->dir, distance) - (1 + k1 * k1)
			* dot_vector3(ray->dir, cone.dir)
			* dot_vector3(distance, cone.dir));
	b *= 2;
	c = dot_vector3(distance, distance) - (1 + k1 * k1)
			* dot_vector3(distance, cone.dir) * dot_vector3(distance, cone.dir);
	if (b * b - 4.0f * a * c < T_RAY_MIN)
		return (0);
	else
		return (calc_intersect(a, b, c, hit));
}

int			find_closest_cone(t_ray ray, t_rtv *rtv, double *t)
{
	int i;
	int current;

	i = 0;
	current = -1;
	while (i < rtv->nbr[CONE])
	{
		if (intersect_cone(rtv->cone[i], &ray, t))
			current = i;
		i++;
	}
	return (current);
}

t_vector3	find_norm_cone(t_vector3 hit_point, t_vector3 center,
		t_vector3 dir, double angle)
{
	t_vector3	norm;
	t_vector3	x;
	double		d;
	double		k;

	norm = sub_vector3(hit_point, center);
	d = dot_vector3(norm, dir) / dot_vector3(dir, dir);
	x = scale_vector3(dir, d);
	k = 1 + tan(angle) * tan(angle);
	x = scale_vector3(x, k);
	norm = normalize(sub_vector3(norm, x));
	return (norm);
}
