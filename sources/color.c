/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsatterf <rsatterf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 20:42:17 by nbethany          #+#    #+#             */
/*   Updated: 2019/10/23 14:57:34 by rsatterf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
#include <stdio.h>

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
	cur_ray.k = 1.0;
	cur_ray.ray.origin = rtv->cam->pos;
	cur_ray.ray.dir = calculate_ray_dir(x, y, rtv); //calculate where ray goes depending on screen parameters (x and y)
	while (cur_ray.k > 0.1f && num_intersect < 3)
	{
		if (calculate_ray(rtv, &cur_ray) != 1)
			break;
		num_intersect++;
	}
	
	//cur_ray.color = intersect_sphere(rtv->sphere, cur_ray.ray);
	//printf("%f\n", cur_ray.color.r);
	//printf("%f\n", cur_ray.color.g);
	//printf("%f\n", cur_ray.color.b);
	return (cur_ray.color);
}

t_vector3 calculate_ray_dir(int x, int y, t_rtv *rtv)
{
	double i;
	double j;
	//double k;
	t_vector3 l;
	//t_vector3 n, v, u;

	(void) rtv;
	i = (2 * ((x + 0.5) / (double) WIDTH)  - 1) * tan(rtv->cam->fov / 2.0 * M_PI / 180.0) * ASPECT_RATIO;
	j = (1 - 2 * ((y + 0.5) / (double) HEIGHT)) * tan(rtv->cam->fov / 2.0 * M_PI / 180.0);

	l = new_vector3(i, j, rtv->cam->dir.z);
	l = normalize(l);
	return (l);

	//n = normalize(rtv->cam->dir);
	//if (n.x == 0 && n.y == 0 && n.z == 1)
	//	l = new_vector3(0, 1, 0);
		//u = cross_vector3(n, new_vector3(0, 1, 0));
	//else
	//	l = new_vector3(0, 0, 1);
		// u = cross_vector3(n, new_vector3(0, 0, 1));
	//u = cross_vector3(n , l);
	//v = cross_vector3(u , n);

}

/*
** Find color, reflective and specular values from item and its number
*/

t_prop find_prop(t_rtv *rtv, int item, int *cur)
{
	t_prop prop;

	prop.color = set_color(0 , 0, 0);
	prop.diffuse = 0;
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

int	calculate_ray(t_rtv *rtv, t_cur_ray *cur_ray)
{
	int 		current;
	int 		item;
	t_vector3	hit_point;
	t_prop		prop;

	current = -1;
	item = find_closest_object(cur_ray->ray, rtv, &hit_point, &current);
	if (item == -1)
		return (0);
	cur_ray->norm = find_norm(rtv, item, &current, hit_point, cur_ray->ray);
	//protection so cur_ray->norm is not zero
	if (len_vector(cur_ray->norm) == 0)
		return (0);
	cur_ray->norm = normalize(cur_ray->norm);
	prop = find_prop(rtv, item, &current);
	get_light(rtv, hit_point, cur_ray, prop);
	cur_ray->k *= prop.diffuse;
	reflect_ray(&cur_ray->ray, cur_ray->norm, hit_point);
	return (1);
}

t_vector3 find_norm(t_rtv *rtv, int item, int *current, t_vector3 hit_point, t_ray ray)
{
	t_vector3 norm;

	norm = new_vector3(0, 0, 0);
	if (item == SPHERE)
		norm = sub_vector3(hit_point, rtv->sphere[*current].center);
	else if (item == PLANE)
	{
		if (dot_vector3(ray.dir, rtv->plane[*current].norm) < 0.f)
			norm = rtv->plane[*current].norm;
		else
			norm = scale_vector3(rtv->plane[*current].norm, -1);
	}
	else if (item == CYLINDER)
        norm = find_norm_cylinder(hit_point, rtv->cylinder[*current].center, rtv->cylinder[*current].dir);
	else if (item == CONE)
		norm = find_norm_cone(hit_point, rtv->cone[*current].center, rtv->cone[*current].dir, rtv->cone[*current].angle);
	return (normalize(norm));
}

void get_light(t_rtv *rtv, t_vector3 hit_point, t_cur_ray *cur_ray, t_prop prop)
{
	int j;
	t_light current_light;
	t_vector3	dist;
	t_ray	light_ray;
	double kd; //diffuse coefficient
	double ks; //specular coefficient
	double brightness;

	j = 0;
	while (j < rtv->nbr[LIGHT])
	{
		current_light = rtv->light[j];
		// light.position - p
		dist = sub_vector3(current_light.pos, hit_point);
		if (dot_vector3(cur_ray->norm, dist) <= 0.f || len_vector(dist) <= 0.f)
		{
			j++;
			continue;
		}
		light_ray.origin = hit_point;
		light_ray.dir = normalize(dist);

		brightness = current_light.brightness * 5000 / (4 * M_PI * pow(len_vector(dist), 2));
		if (!is_in_shadow(&light_ray, rtv, len_vector(dist)))
		{
			kd = diffuse(light_ray, cur_ray->norm);
			kd < 0 ? kd = 0 : 0;
			color_diffuse(&cur_ray->color, kd, current_light, prop, brightness);
			ks = specular(light_ray, cur_ray->norm, &cur_ray->ray, prop);
			ks < 0 ? ks = 0 : 0;
			color_diffuse(&cur_ray->color, ks, current_light, prop, brightness);
		}
		//else
		//	color_diffuse(&cur_ray->color, AMBIENT, current_light, prop, brightness);
		j++;
	}
}

int find_closest_object(t_ray ray, t_rtv *rtv, t_vector3 *hit_vector, int *cur_item)
{
	int i;
	double distance;
	int closest[4];

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
	i = 0;
	while (i < 4)
    {
        if (closest[i] > -1)
        {
            *cur_item = closest[i];
            return(i + 2);
        }
        i++;
    }
	    return (-1);
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

void	reflect_ray(t_ray *ray, t_vector3 norm, t_vector3 hit_vector)
{
	double f;
	t_vector3 tmp;

	ray->origin = hit_vector;
	f = dot_vector3(ray->dir, norm);
	tmp = scale_vector3(norm, 2.f * f);
	ray->dir = sub_vector3(ray->dir, tmp);
	ray->dir = normalize(ray->dir);
}