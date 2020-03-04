/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_valid.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsatterf <rsatterf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/02 14:59:57 by rsatterf          #+#    #+#             */
/*   Updated: 2020/03/03 13:32:07 by rsatterf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int	data_color(char *str, t_color *vec, int k, t_rtv *rtv)
{
	int i;

	i = 0;
	while (i != k)
	{
		str++;
		i++;
	}
	if (valid_count(str, rtv) != 0)
		return (-1);
	vec->r = ft_atoi(str);
	while (*str != ' ')
		str++;
	str++;
	vec->g = ft_atoi(str);
	while (*str != ' ')
		str++;
	vec->b = ft_atoi(str);
	if (((vec->r >= 0) && (vec->r <= 255)) && ((vec->g >= 0)
		&& (vec->g <= 255)) && ((vec->b >= 0) && (vec->b <= 255)))
		return (0);
	else
		return (-1);
}

int	data_vector(char *str, t_vector3 *vec, int k, t_rtv *rtv)
{
	int i;

	i = 0;
	while (i != k)
	{
		str++;
		i++;
	}
	if (valid_count(str, rtv) != 0)
		return (-1);
	vec->x = ft_atoi(str);
	while (*str != ' ')
		str++;
	str++;
	vec->y = ft_atoi(str);
	while (*str != ' ')
		str++;
	vec->z = ft_atoi(str);
	return (0);
}

int	data_vector_norm(char *str, t_vector3 *vec, int k, t_rtv *rtv)
{
	t_vector3 new_vector;

	rtv->j = 0;
	while (rtv->j != k)
	{
		str++;
		rtv->j++;
	}
	if (valid_count(str, rtv) != 0)
		return (-1);
	new_vector.x = ft_atoi(str);
	while (*str != ' ')
		str++;
	str++;
	new_vector.y = ft_atoi(str);
	while (*str != ' ')
		str++;
	new_vector.z = ft_atoi(str);
	if (len_vector(new_vector) < T_RAY_MIN)
		return (-1);
	new_vector = normalize(new_vector);
	vec->x = new_vector.x;
	vec->y = new_vector.y;
	vec->z = new_vector.z;
	return (0);
}

int	valid_prop(t_prop *object)
{
	if ((object->specular < 0) || (object->reflection < 0)
		|| (object->reflection > 100))
		return (-1);
	else
		return (0);
}
