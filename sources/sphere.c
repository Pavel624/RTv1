/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsatterf <rsatterf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 21:28:51 by nbethany          #+#    #+#             */
/*   Updated: 2019/10/23 14:59:57 by rsatterf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
#include <stdio.h>

t_sphere new_sphere(t_vector3 center, double radius)
{
	t_sphere sphere;

	sphere.center = center;
	sphere.radius = radius;
	return (sphere);
}

int     intersect_sphere(t_sphere sphere, t_ray *ray, double *hit)
{
    double a, b, c;
    t_vector3 distance;

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

int find_closest_sphere(t_ray ray, t_rtv *rtv, double *t)
{
	int i, current;

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

int     calc_intersect(double k1, double k2, double k3, double *hit)
{
    double sqrt_discr;
    double t1, t2;

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