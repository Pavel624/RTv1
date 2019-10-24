/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbethany <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 07:34:28 by nbethany          #+#    #+#             */
/*   Updated: 2019/10/24 07:34:32 by nbethany         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_plane new_plane(t_vector3 norm, double point)
{
	t_plane plane;

	plane.norm = norm;
	plane.point = point;
	return (plane);
}

int intersect_plane(t_plane plane, t_ray ray, double *hit)
{
	double dot;
	double t1;

	dot = dot_vector3(ray.dir,ray.dir);
	if (dot != 0)
	{
		t1 = (-dot_vector3(ray.origin, plane.norm) + plane.point) / dot_vector3(ray.dir, plane.norm);
		if (t1 > 0.01f && (t1 < *hit || *hit == -1))
		{
			*hit = t1;
			return (1);
		}
		else
			return (0);
	}
	else
		return (0);
}

int find_closest_plane(t_ray ray, t_rtv *rtv, double *t)
{
	int i, current;

	i = 0;
	current = -1;
	while (i < rtv->nbr[PLANE])
	{
		if (intersect_plane(rtv->plane[i], ray, t))
			current = i;
		i++;
	}
	return (current);
}