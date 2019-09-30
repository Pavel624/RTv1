/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector3.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbethany <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/26 21:25:31 by nbethany          #+#    #+#             */
/*   Updated: 2019/09/26 21:25:35 by nbethany         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR3_H
# define VECTOR3_H

# include "../libft/libft.h"

typedef struct	s_vector3
{
	double		x;
	double		y;
	double		z;
}				t_vector3;

t_vector3	*new_vector3(double x, double y, double z);
t_vector3	*add_vector3(t_vector3 *vec1, t_vector3 *vec2, int free);
t_vector3	*sub_vector3(t_vector3 *vec1, t_vector3 *vec2, int free);
double		scalar_vector3(t_vector3 *vec1, t_vector3 *vec2, int free);
t_vector3	*mult_vector3(t_vector3 *vec1, t_vector3 *vec2, int free);

#endif