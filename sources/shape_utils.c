/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shape_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbethany <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/02 22:06:38 by nbethany          #+#    #+#             */
/*   Updated: 2020/03/02 22:06:39 by nbethany         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_prop		find_prop(t_rtv *rtv, int item, int *cur)
{
	t_prop	prop;

	prop.color = set_color(0, 0, 0);
	prop.reflection = 0;
	prop.specular = 0;
	if (item == SPHERE)
		prop = rtv->sphere[*cur].prop;
	else if (item == PLANE)
		prop = rtv->plane[*cur].prop;
	else if (item == CYLINDER)
		prop = rtv->cylinder[*cur].prop;
	else if (item == CONE)
		prop = rtv->cone[*cur].prop;
	return (prop);
}

t_vector3	find_norm_plane(t_rtv *rtv, int *current, t_ray ray)
{
	t_vector3	norm;

	norm = new_vector3(0, 0, 0);
	if (dot_vector3(ray.dir, rtv->plane[*current].norm) < 0.f)
		norm = rtv->plane[*current].norm;
	else
		norm = scale_vector3(rtv->plane[*current].norm, -1);
	return (normalize(norm));
}

t_vector3	find_norm_not_plane(t_rtv *rtv, int item,
		int *current, t_vector3 hit_point)
{
	t_vector3	norm;

	norm = new_vector3(0, 0, 0);
	if (item == SPHERE)
		norm = sub_vector3(hit_point, rtv->sphere[*current].center);
	else if (item == CYLINDER)
		norm = find_norm_cylinder(hit_point,
				rtv->cylinder[*current].center, rtv->cylinder[*current].dir);
	else if (item == CONE)
		norm = find_norm_cone(hit_point, rtv->cone[*current].center,
				rtv->cone[*current].dir, rtv->cone[*current].angle);
	return (normalize(norm));
}

int			find_closest_object(t_ray ray, t_rtv *rtv,
		t_vector3 *hit_vector, int *cur_item)
{
	int		i;
	double	distance;
	int		closest[4];

	distance = -1;
	closest[0] = find_closest_sphere(ray, rtv, &distance);
	closest[1] = find_closest_plane(ray, rtv, &distance);
	closest[2] = find_closest_cylinder(ray, rtv, &distance);
	closest[3] = find_closest_cone(ray, rtv, &distance);
	*hit_vector = add_vector3(scale_vector3(ray.dir, distance), ray.origin);
	i = 3;
	while (closest[i] == -1 && i > 0)
		i--;
	while (--i >= 0)
		closest[i] = -1;
	i = -1;
	while (++i < 4)
	{
		if (closest[i] > -1)
		{
			*cur_item = closest[i];
			return (i + 2);
		}
	}
	return (-1);
}

int			calc_intersect(double k1, double k2, double k3, double *hit)
{
	double	sqrt_discr;
	double	t1;
	double	t2;

	sqrt_discr = sqrtf(k2 * k2 - 4 * k1 * k3);
	t1 = (-k2 + sqrt_discr) / (2 * k1);
	t2 = (-k2 - sqrt_discr) / (2 * k1);
	if (t1 > t2 || t1 < T_RAY_MIN)
		t1 = t2;
	if (t1 > T_RAY_MIN && (t1 < *hit || *hit == -1))
	{
		*hit = t1;
		return (1);
	}
	else
		return (0);
}
