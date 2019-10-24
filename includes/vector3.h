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
# include <math.h>

typedef struct	s_vector3
{
	double		x;
	double		y;
	double		z;
}				t_vector3;

t_vector3	new_vector3(double x, double y, double z);
t_vector3	add_vector3(t_vector3 vec1, t_vector3 vec2);
t_vector3	sub_vector3(t_vector3 vec1, t_vector3 vec2);
double		dot_vector3(t_vector3 vec1, t_vector3 vec2);
t_vector3	cross_vector3(t_vector3 vec1, t_vector3 vec2);
t_vector3	scale_vector3(t_vector3 vec, double nbr);
t_vector3 	normalize(t_vector3 vec);
double 		len_vector(t_vector3 vec);

#endif