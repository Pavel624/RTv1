/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_op.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbethany <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 01:19:56 by nbethany          #+#    #+#             */
/*   Updated: 2019/10/24 01:19:58 by nbethany         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
#include <stdio.h>

void color_diffuse(t_color *color, double f, t_light light, t_prop prop, double dist2)
{
	color->r += f * (prop.color.r / 255) * (light.intensity.r / 255) / dist2;
	color->g += f * (prop.color.g / 255) * (light.intensity.g / 255) / dist2;
	color->b += f * (prop.color.b / 255) * (light.intensity.b / 255) / dist2;
}

void color_phong(t_color *color, double f, t_light light, double coef, double dist2)
{
	color->r += f * coef * (light.intensity.r / 255) / dist2;
	color->g += f * coef * (light.intensity.g / 255) / dist2;
	color->b += f * coef * (light.intensity.b / 255) / dist2;
}

double diffuse(t_ray light_ray, t_vector3 norm, double k)
{
	return (dot_vector3(light_ray.dir, norm) * k / (len_vector(norm) * len_vector(light_ray.dir)));
}

double phong(t_ray light_ray, t_vector3 norm, t_ray *ray, t_prop prop)
{
	t_vector3	dir;
	double	k;
	double tmp;

	(void) ray;
	tmp = dot_vector3(norm, light_ray.dir);
	dir = scale_vector3(norm, 2 * tmp);
	dir = sub_vector3(dir, light_ray.dir);
	if (dot_vector3(dir, dir) != 0)
	{
		dir = normalize(dir);
		k = dot_vector3(dir, norm);
		if (k < 0)
			return (0);
		k = pow(k / (len_vector(dir) * len_vector(norm)), prop.specular);
	}
	else
		k = 0;
	return (k);
}

int is_in_shadow(t_ray light_ray, t_rtv *rtv, double t)
{
	int i;

	i = 0;
	while (i < rtv->nbr[SPHERE])
	{
		if (intersect_sphere(rtv->sphere[i], light_ray, &t))
			return (1);
		i++;
	}
	i = 0;
    while (i < rtv->nbr[PLANE])
    {
        if (intersect_plane(rtv->plane[i], light_ray, &t))
            return (1);
        i++;
    }
	i = 0;
	while (i < rtv->nbr[CYLINDER])
	{
		if (intersect_cylinder(rtv->cylinder[i], light_ray, &t))
			return (1);
		i++;
	}
	i = 0;
	while (i < rtv->nbr[CONE])
	{
		if (intersect_cone(rtv->cone[i], light_ray, &t))
			return (1);
		i++;
	}
	return (0);
}