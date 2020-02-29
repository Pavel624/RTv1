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

void color_diffuse(t_color *color, double k, t_light light, t_prop prop, double brightness)
{
	color->r += k * (prop.color.r / 255) * (light.color.r / 255) * brightness;
	color->g += k * (prop.color.g / 255) * (light.color.g / 255) * brightness;
	color->b += k * (prop.color.b / 255) * (light.color.b / 255) * brightness;
	color->r > 255 ? color->r = 255 : 0;
	color->g > 255 ? color->g = 255 : 0;
	color->b > 255 ? color->b = 255 : 0;
	color->r < 0 ? color->r = 0 : 0;
	color->g < 0 ? color->g = 0 : 0;
	color->b < 0 ? color->b = 0 : 0;
}

void color_specular(t_color *color, double k, t_light light, double brightness)
{
	color->r += k  * (light.color.r / 255) * brightness;
	color->g += k  * (light.color.g / 255) * brightness;
	color->b += k  * (light.color.b / 255) * brightness;
	color->r > 255 ? color->r = 255 : 0;
	color->g > 255 ? color->g = 255 : 0;
	color->b > 255 ? color->b = 255 : 0;
	color->r < 0 ? color->r = 0 : 0;
	color->g < 0 ? color->g = 0 : 0;
	color->b < 0 ? color->b = 0 : 0;
}

double diffuse(t_ray light_ray, t_vector3 norm)
{
	return (dot_vector3(light_ray.dir, norm) / (len_vector(norm) * len_vector(light_ray.dir)));
}

double specular(t_ray light_ray, t_vector3 norm, t_ray *ray, t_prop prop)
{
	t_vector3	dir;
	double	k;

	dir = sub_vector3(light_ray.dir, ray->dir);
	if (len_vector(dir) > T_RAY_MIN)
	{
		dir = normalize(dir);
		k = dot_vector3(dir, norm);
		k < 0 ? k = 0 : k;
		k = SPECULAR_COEF * pow (k, prop.specular);
	}
	else
		k = 0;
	return (k);
}

int is_in_shadow(t_ray *light_ray, t_rtv *rtv, double t)
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