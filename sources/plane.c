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

	dot = dot_vector3(plane.norm,ray.dir);
	if (fabs(dot) > 0.00001f)
	{
	    t1 = (plane.point - dot_vector3(plane.norm, ray.origin)) / dot;
		if (t1 > 0.001f && (t1 < *hit || *hit == -1))
		{
			*hit = t1;
			return (1);
		}
		else
			return (0);
	}
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