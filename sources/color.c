/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
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

t_color	calculate_color(t_rtv *rtv, int x, int y)
{
	t_cur_ray	cur_ray;
	int			num_intersect;

	cur_ray.color = set_color(0, 0, 0);
	num_intersect = 0;
	cur_ray.ray.origin = rtv->cam->pos;
	cur_ray.ray.dir = calculate_ray_dir(x, y, rtv); //calculate where ray goes denending on screen parametrs (x and y)
	while (num_intersect < 1)
	{
		if (calculate_ray(rtv, &cur_ray) != 1)
			break;
		num_intersect++;
	}
	return (cur_ray.color);
}

t_vector3 calculate_ray_dir(int x, int y, t_rtv *rtv)
{
	t_vector3	i;
	t_vector3	j;
	t_vector3	k;
	t_vector3	l;

	k = rtv->cam->dir;
	l = new_vector3(0.0f, 1.0f, 0.0f);
	i = cross_vector3(k, l);
	j = cross_vector3(i, k); //screen plane consisting of 2 perpendicular vectors
	//i, j, k - basis for l vector
	l.x = (WIDTH - 2.0 * (double) x) / WIDTH * i.x + (HEIGHT - 2.0 * (double) y) / WIDTH * j.x + FOV * k.x;
	l.y = (WIDTH - 2.0 * (double) x) / WIDTH * i.y + (HEIGHT - 2.0 * (double) y) / WIDTH * j.y + FOV * k.y;
	l.z = (WIDTH - 2.0 * (double) x) / WIDTH * i.z + (HEIGHT - 2.0 * (double) y) / WIDTH * j.z + FOV * k.z;
	l = normalize(l);
	return (l);
}

int			calculate_ray(t_rtv *rtv, t_cur_ray *cur_ray)
{
	t_vector3	hit_vector;
	double 		hit;

	intersect_sphere(rtv->sphere, cur_ray->ray, &hit);
	if (hit == 0.0f)
		return (0);
	hit_vector = add_vector3(scale_vector3(cur_ray->ray.dir, hit), cur_ray->ray.origin);
	cur_ray->norm = sub_vector3(hit_vector, rtv->sphere->center);
	if (dot_vector3(cur_ray->norm, cur_ray->norm) == 0)
		return (0);
	cur_ray->norm = normalize(cur_ray->norm);
	get_light(rtv, hit_vector, cur_ray);
	return (1);
}

void get_light(t_rtv *rtv, t_vector3 hit_vector, t_cur_ray *cur_ray)
{
	t_light 	light;
	t_vector3 	distance;
	t_ray 		light_ray;
	double 		f;

	light = rtv->light;
	distance = sub_vector3(light.pos, hit_vector);
	light_ray.origin = hit_vector;
	light_ray.dir = normalize(distance);

	f = light_shape(light_ray, cur_ray->norm);
	get_light_color(&cur_ray->color, f, rtv->light);
}

double light_shape(t_ray light_ray, t_vector3 norm)
{
	double	f;

	f = dot_vector3(light_ray.dir, norm);
	if (f < 0)
		return (0);
	return (f);
}

void get_light_color(t_color *color, double f, t_light light)
{
	color->r += f * light.intensity.r;
	color->g += f * light.intensity.g;
	color->b += f * light.intensity.b;
}