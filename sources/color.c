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
	while (cur_ray.k > 0.0f && num_intersect < 4)
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
	t_vector3 l;

	(void) rtv;
	i =  (2 * (x + 0.5) / (float) WIDTH  - 1) * tan(FOV / 2. * M_PI / 180) * WIDTH / (double) HEIGHT;
	j = -(2 * (y + 0.5) / (float) HEIGHT - 1) * tan(FOV / 2. * M_PI / 180);

	l = new_vector3(i, j, 1);
	l = normalize(l);
	return (l);
}

//find color, reflective and specular values from item and it's number

t_prop find_prop(t_rtv *rtv, int item, int *cur)
{
	t_prop prop;

	if (item == SPHERE)
		prop = rtv->sphere[*cur].prop;
	else if (item == PLANE)
		prop = rtv->plane[*cur].prop;
    else if (item == CYLINDER)
        prop = rtv->cylinder[*cur].prop;
	else
		prop = rtv->sphere[*cur].prop; // TODO change this line
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
	cur_ray->k *= prop.reflective;
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
	{
        norm = find_norm_cylinder(hit_point, rtv->cylinder[*current].center, rtv->cylinder[*current].dir);
    }
	return (norm);
}

void get_light(t_rtv *rtv, t_vector3 hit_point, t_cur_ray *cur_ray, t_prop prop)
{
	int j;
	t_light current_light;
	t_vector3	dist;
	t_ray	light_ray;
	double k;

	j = 0;
	while (j < rtv->nbr[LIGHT])
	{
		current_light = rtv->light[j];
		// light.position - p
		dist = sub_vector3(current_light.pos, hit_point);
		if (dot_vector3(cur_ray->norm, dist) <= 0)
		{
			j++;
			continue;
		}
		light_ray.origin = hit_point;
		light_ray.dir = normalize(dist);
		if (!is_in_shadow(light_ray, rtv, len_vector(dist)))
		{
			k = diffuse(light_ray, cur_ray->norm, cur_ray->k);
			color_diffuse(&cur_ray->color, k, current_light, prop);
			k = phong(light_ray, cur_ray->norm, &cur_ray->ray, prop);
			color_phong(&cur_ray->color, k, current_light, cur_ray->k);
		}
		j++;
	}
}

int find_closest_object(t_ray ray, t_rtv *rtv, t_vector3 *hit_vector, int *cur_item)
{
	int i;
	int k;
	double closest_dist;
	int closest[3];

	closest_dist = MAXFLOAT;
    i = 0;
    k = 0;
	double dist[] = {-1, -1, -1};
	closest[0] = find_closest_sphere(ray, rtv, &dist[0]);
	closest[1] = find_closest_plane(ray, rtv, &dist[1]);
    closest[2] = find_closest_cylinder(ray, rtv, &dist[2]);

    while (i < 3)
    {
        if (dist[i] < closest_dist && dist[i] > 0)
        {
            closest_dist = dist[i];
            *cur_item = closest[i];
            k = i;
        }
        i++;
    }
    *hit_vector = add_vector3(scale_vector3(ray.dir, closest_dist), ray.origin);
    if (closest_dist < MAXFLOAT)
        return (k + 2);
    else
	    return (-1);
}

int find_closest_sphere(t_ray ray, t_rtv *rtv, double *t)
{
	int i, current;

	i = 0;
	current = -1;
	while (i < rtv->nbr[SPHERE])
	{
		if (intersect_sphere(rtv->sphere[i], ray, t))
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