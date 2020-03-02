/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbethany <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/02 21:59:16 by nbethany          #+#    #+#             */
/*   Updated: 2020/03/02 21:59:18 by nbethany         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_vector3	calculate_ray_dir(int x, int y, t_rtv *rtv)
{
	double		i;
	double		j;
	t_vector3	ray;
	t_vector3	image_point;

	i = (2 * ((x + 0.5) / (double)WIDTH) - 1) *
		tan(rtv->cam->fov / 2.0 * M_PI / 180.0) * ASPECT_RATIO;
	j = (1 - 2 * ((y + 0.5) / (double)HEIGHT)) *
		tan(rtv->cam->fov / 2.0 * M_PI / 180.0);
	image_point = add_vector3(scale_vector3(rtv->cam->i, i),
			scale_vector3(rtv->cam->j, j));
	image_point = add_vector3(image_point, rtv->cam->pos);
	image_point = add_vector3(image_point, rtv->cam->dir);
	ray = sub_vector3(image_point, rtv->cam->pos);
	ray = normalize(ray);
	return (ray);
}

int			calculate_ray(t_rtv *rtv, t_cur_ray *cur_ray)
{
	int			current;
	int			item;
	t_vector3	hit_point;
	t_prop		prop;

	current = -1;
	item = find_closest_object(cur_ray->ray, rtv, &hit_point, &current);
	if (item == -1)
		return (0);
	if (item == PLANE)
		cur_ray->norm = find_norm_plane(rtv, &current, cur_ray->ray);
	else
		cur_ray->norm = find_norm_not_plane(rtv, item, &current, hit_point);
	if (len_vector(cur_ray->norm) < T_RAY_MIN)
		return (0);
	cur_ray->norm = normalize(cur_ray->norm);
	prop = find_prop(rtv, item, &current);
	get_light(rtv, hit_point, cur_ray, prop);
	cur_ray->k *= prop.reflection / 100.f;
	reflect_ray(&cur_ray->ray, cur_ray->norm, hit_point);
	return (1);
}

void		reflect_ray(t_ray *ray, t_vector3 norm, t_vector3 hit_vector)
{
	double		k;
	t_vector3	tmp;

	ray->origin = hit_vector;
	k = dot_vector3(ray->dir, norm);
	tmp = scale_vector3(norm, 2.f * k);
	ray->dir = sub_vector3(ray->dir, tmp);
	ray->dir = normalize(ray->dir);
}
