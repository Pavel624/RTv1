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

static double	get_brightness(t_light light, t_vector3 dist)
{
	return (light.brightness * BRIGHTNESS / (M_PI * pow(len_vector(dist), 2)));
}

static	double	diffuse(t_ray light_ray, t_cur_ray *cur_ray)
{
	double		kd;

	kd = cur_ray->k * dot_vector3(light_ray.dir, cur_ray->norm)
			/ (len_vector(cur_ray->norm) * len_vector(light_ray.dir));
	kd < 0 ? kd = 0 : 0;
	return (kd);
}

static	double	specular(t_ray light_ray, t_cur_ray *cur_ray, t_prop prop)
{
	t_vector3	dir;
	double		k;

	dir = sub_vector3(light_ray.dir, cur_ray->ray.dir);
	if (len_vector(dir) > T_RAY_MIN)
	{
		dir = normalize(dir);
		k = dot_vector3(dir, cur_ray->norm);
		k < 0 ? k = 0 : k;
		k = cur_ray->k * SPECULAR_COEF * pow(k, prop.specular);
	}
	else
		k = 0;
	return (k);
}

static	int		is_in_shadow(t_ray *light_ray, t_rtv *rtv, double t)
{
	int			i;

	i = -1;
	while (++i < rtv->nbr[SPHERE])
		if (intersect_sphere(rtv->sphere[i], light_ray, &t))
			return (1);
	i = -1;
	while (++i < rtv->nbr[PLANE])
		if (intersect_plane(rtv->plane[i], light_ray, &t))
			return (1);
	i = -1;
	while (++i < rtv->nbr[CYLINDER])
		if (intersect_cylinder(rtv->cylinder[i], light_ray, &t))
			return (1);
	i = -1;
	while (++i < rtv->nbr[CONE])
		if (intersect_cone(rtv->cone[i], light_ray, &t))
			return (1);
	return (0);
}

void			get_light(t_rtv *rtv, t_vector3 hit_point,
		t_cur_ray *cur_ray, t_prop prop)
{
	int			j;
	t_vector3	dist;
	t_ray		light_ray;
	double		k[2];
	double		bright;

	j = -1;
	while (++j < rtv->nbr[LIGHT])
	{
		dist = sub_vector3(rtv->light[j].pos, hit_point);
		if (dot_vector3(cur_ray->norm, dist) < T_RAY_MIN)
			continue;
		light_ray.origin = add_vector3(hit_point, cur_ray->norm);
		light_ray.dir = normalize(dist);
		bright = get_brightness(rtv->light[j], dist);
		if (!is_in_shadow(&light_ray, rtv, len_vector(dist)))
		{
			k[0] = diffuse(light_ray, cur_ray);
			color_diffuse(&cur_ray->color, k[0] * bright, rtv->light[j], prop);
			k[1] = specular(light_ray, cur_ray, prop);
			color_specular(&cur_ray->color, k[1], rtv->light[j], bright);
		}
		else
			color_specular(&cur_ray->color, AMBIENT, rtv->light[j], bright);
	}
}
