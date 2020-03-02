/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_valid.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsatterf <rsatterf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/02 14:59:57 by rsatterf          #+#    #+#             */
/*   Updated: 2020/03/02 15:14:07 by rsatterf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int		valid_count(char *str)
{
	int i;
	int j;
	int k;
	int e;

	i = 0;
	k = 0;
	j = 0;
	e = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '-')
			i++;
		else if (str[i] >= 48 && str[i] <= 57)
		{
			e++;
			while (str[i] >= 48 && str[i] <= 57 && str[i] != '\0')
				i++;
		}
		else if (str[i] == ' ')
		{
			j++;
			i++;
		}
		else if (str[i] == ')')
		{
			k++;
			i++;
		}
		else
			return (-1);
	}
	if ((j != 2) || (k != 1) || (e != 3))
		return (-1);
	return (0);
}

int		valid_count2(char *str)
{
	int i;
	int k;

	i = 0;
	k = 0;
	while (str[i] != '\0')
	{
		if ((str[i] >= 48 && str[i] <= 57) || (str[i] == '-'))
			i++;
		else if (str[i] == ')')
		{
			k++;
			i++;
		}
		else
			return (-1);
	}
	if (k != 1)
		return (-1);
	return (0);
}

int		data_color(char *str, t_color *vec, int k)
{
	int i;

	i = 0;
	while (i != k)
	{
		str++;
		i++;
	}
	if (valid_count(str) != 0)
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

int	data_vector(char *str, t_vector3 *vec, int k)
{
	int i;

	i = 0;
	while (i != k)
	{
		str++;
		i++;
	}
	if (valid_count(str) != 0)
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

int		data_vector_norm(char *str, t_vector3 *vec, int k)
{
	int i;
	t_vector3 new_vector;

	i = 0;
	while (i != k)
	{
		str++;
		i++;
	}
	if (valid_count(str) != 0)
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

int		valid_prop(t_prop *object)
{
	if ((object->specular < 0) || (object->reflection < 0)
		|| (object->reflection > 100))
		return (-1);
	else
		return (0);
}
