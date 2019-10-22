/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbethany <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 20:42:17 by nbethany          #+#    #+#             */
/*   Updated: 2019/10/21 20:42:18 by nbethany         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_color set_color(double r, double g, double b)
{
    t_color color;

    color.r = r;
    color.g = g;
    color.b = b;
    return (color);
}

t_color	calculate_color( t_rtv *rtv, int x, int y)
{
	t_cur_ray cur_ray;

	cur_ray.color = set_color(0, 0, 0);
	cur_ray.k = 1.0f;
	cur_ray.ray.origin = rtv->cam->pos;
	cur_ray.ray.dir = calculate_ray_dir(x, y, rtv);
	calculate_ray(rtv, &cur_ray);
	return (cur_ray.color);
}

t_vector3 calculate_ray_dir(int x, int y, t_rtv *rtv)
{
	t_vector3	i;
	t_vector3	j;
	t_vector3	tmp;
	t_vector3	ray;

	tmp = rtv->cam->dir;
	ray = new_vector3(0, 0, 1);
	i = cross_vector3(tmp, ray);
	j = cross_vector3(i, tmp);
	ray.x = (1 - 2 * (double) x/ WIDTH) * i.x + (ASPECT_RATIO - 2 * (double)y / WIDTH) * j.x + FOV * tmp.x;
	ray.y = (1 - 2 * (double) x/ WIDTH) * i.y + (ASPECT_RATIO - 2 * (double)y / WIDTH) * j.y + FOV * tmp.y;
	ray.z = (1 - 2 * (double) x/ WIDTH) * i.z + (ASPECT_RATIO - 2 * (double)y / WIDTH) * j.z + FOV * tmp.z;
	ray = normalize(ray);
	return (ray);
}

void			calculate_ray(t_rtv *rtv, t_cur_ray *cur_ray)
{
	cur_ray->norm = sub_vector3(cur_ray->ray.origin, rtv->sphere.center);
	if (dot_vector3(cur_ray->norm, cur_ray->norm) == 0)
		return ;
	cur_ray->norm = normalize(cur_ray->norm);
	get_light(rtv, cur_ray);
	return ;
}

void get_light(t_rtv *rtv, t_cur_ray *cur_ray)
{
	t_light light;
	t_vector3 distance;
	t_ray 	light_ray;
	double f;

	light = rtv->light;
	distance = sub_vector3(light.pos, cur_ray->ray.origin);
	light_ray.origin = cur_ray->ray.origin;
	light_ray.dir = normalize(distance);

	f = light_shape(light_ray, cur_ray->norm, cur_ray->k);
}

double light_shape(t_ray light_ray, t_vector3 norm, double k)
{
	double	f;

	f = dot_vector3(light_ray.dir, norm) * k;
	return (f);
}