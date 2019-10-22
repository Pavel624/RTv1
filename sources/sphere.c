/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbethany <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 21:28:51 by nbethany          #+#    #+#             */
/*   Updated: 2019/10/21 21:28:53 by nbethany         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_sphere *new_sphere(t_vector3 center, double radius, t_color color)
{
	t_sphere *sphere;

	if (!(sphere = (t_sphere*)malloc(sizeof(t_sphere))))
		return (NULL);
	sphere->center = center;
	sphere->radius = radius;
	sphere->color = color;
	return (sphere);
}

int     intersect_sphere(t_sphere *sphere, t_ray ray, double *hit)
{
    double k1, k2, k3;
    double discriminant;
    t_vector3 distance;

    k1 = dot_vector3(ray.dir, ray.dir);
    distance = sub_vector3(ray.origin, sphere->center);
    k2 = 2 * dot_vector3(distance, ray.dir);
    k3 = dot_vector3(distance, distance) - sphere->radius * sphere->radius;
    discriminant = k2 * k2 - 4 * k1 * k3;
    if (discriminant < 0)
        return (0);
    else
		return (calc_intersect(k1, k2, k3, hit));
}

int     calc_intersect(double k1, double k2, double k3, double *hit)
{
    double sqrt_discr;
    double t1, t2;

    sqrt_discr = sqrtf(k2 * k2 - 4 * k1 * k3);
    t1 = (-k2 + sqrt_discr) / (2 * k1);
    t2 = (-k2 - sqrt_discr) / (2 * k1);
    if (t1 > t2 && t2 > FOV)
    	t1 = t2;
    if (t1 > 0.001f)
    {
        *hit = t1;
        return (1);
    }
    else
        return (0);
}