/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbethany <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/26 21:28:51 by nbethany          #+#    #+#             */
/*   Updated: 2019/09/26 21:28:53 by nbethany         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/vector3.h"

t_vector3	*new_vector3(double x, double y, double z)
{
	t_vector3 *vec_new;

	if (!(vec_new = malloc(sizeof(t_vector3))))
		return (NULL);
	vec_new->x = x;
	vec_new->y = y;
	vec_new->z = z;
	return (vec_new);
}

t_vector3	*add_vector3(t_vector3 *vec1, t_vector3 *vec2, int free)
{
	t_vector3 *vec_add;

	if (!vec1 || !vec2)
		return (NULL);
	vec_add = new_vector3(vec1->x + vec2->x, vec1->y + vec2->y, vec1->z + vec2->z);
	if (free)
	{
		ft_memdel((void **) &vec1);
		ft_memdel((void **) &vec2);
	}
	return (vec_add);
}

t_vector3	*sub_vector3(t_vector3 *vec1, t_vector3 *vec2, int free)
{
	t_vector3 *vec_sub;

	if (!vec1 || !vec2)
		return (NULL);
	vec_sub = new_vector3(vec1->x - vec2->x, vec1->y - vec2->y, vec1->z - vec2->z);
	if (free)
	{
		ft_memdel((void **) &vec1);
		ft_memdel((void **) &vec2);
	}
	return (vec_sub);
}

double		scalar_vector3(t_vector3 *vec1, t_vector3 *vec2, int free)
{
	double scalar;

	scalar = vec1->x * vec2->x + vec1->y * vec2->y + vec1->z * vec2->z;
	if (free)
	{
		ft_memdel((void **) &vec1);
		ft_memdel((void **) &vec2);
	}
	return (scalar);
}

t_vector3	*mult_vector3(t_vector3 *vec1, t_vector3 *vec2, int free)
{
	t_vector3 *vec_mult;

	if (!vec1 || !vec2)
		return (NULL);
	vec_mult = new_vector3(vec1->y * vec2->z - vec1->z * vec2->y, vec1->z * vec2->x - vec1->x * vec2->z, vec1->x * vec2->y - vec1->y * vec2->x);
	if (free)
	{
		ft_memdel((void **) &vec1);
		ft_memdel((void **) &vec2);
	}
	return (vec_mult);
}

t_vector3	*mult_nbr_vector3(t_vector3 *vec, double nbr, int free)
{
	t_vector3 *vec_mult;

	if (!vec)
		return (NULL);
	vec_mult = new_vector3(nbr * vec->x, nbr * vec->y, nbr * vec->z);
	if (free)
		ft_memdel((void **) &vec);
	return (vec_mult);
}