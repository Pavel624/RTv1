/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector3_op2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbethany <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/02 21:42:55 by nbethany          #+#    #+#             */
/*   Updated: 2020/03/02 21:42:56 by nbethany         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector3.h"

t_vector3	scale_vector3(t_vector3 vec, double nbr)
{
	t_vector3	vec_mult;

	vec_mult.x = nbr * vec.x;
	vec_mult.y = nbr * vec.y;
	vec_mult.z = nbr * vec.z;
	return (vec_mult);
}

t_vector3	normalize(t_vector3 vec)
{
	double	len;

	len = sqrtf(pow(vec.x, 2) + pow(vec.y, 2) + pow(vec.z, 2));
	vec.x /= len;
	vec.y /= len;
	vec.z /= len;
	return (vec);
}

double		len_vector(t_vector3 vec)
{
	double	len;

	len = sqrtf(pow(vec.x, 2) + pow(vec.y, 2) + pow(vec.z, 2));
	return (len);
}
