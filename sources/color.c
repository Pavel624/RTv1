/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsatterf <rsatterf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 20:42:17 by nbethany          #+#    #+#             */
/*   Updated: 2020/03/03 12:26:52 by rsatterf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_color	set_color(double r, double g, double b)
{
	t_color color;

	color.r = r;
	color.g = g;
	color.b = b;
	return (color);
}

void	color_diffuse(t_color *color, double k_mult_bright,
		t_light light, t_prop prop)
{
	color->r += k_mult_bright * (prop.color.r / 255) * (light.color.r / 255);
	color->g += k_mult_bright * (prop.color.g / 255) * (light.color.g / 255);
	color->b += k_mult_bright * (prop.color.b / 255) * (light.color.b / 255);
	color->r > 255 ? color->r = 255 : 0;
	color->g > 255 ? color->g = 255 : 0;
	color->b > 255 ? color->b = 255 : 0;
	color->r < 0 ? color->r = 0 : 0;
	color->g < 0 ? color->g = 0 : 0;
	color->b < 0 ? color->b = 0 : 0;
}

void	color_specular(t_color *color, double k,
		t_light light, double brightness)
{
	color->r += k * (light.color.r / 255) * brightness;
	color->g += k * (light.color.g / 255) * brightness;
	color->b += k * (light.color.b / 255) * brightness;
	color->r > 255 ? color->r = 255 : 0;
	color->g > 255 ? color->g = 255 : 0;
	color->b > 255 ? color->b = 255 : 0;
	color->r < 0 ? color->r = 0 : 0;
	color->g < 0 ? color->g = 0 : 0;
	color->b < 0 ? color->b = 0 : 0;
}

t_color	calculate_color(t_rtv *rtv, int x, int y)
{
	t_cur_ray	cur_ray;
	int			num_intersect;

	cur_ray.color = set_color(0, 0, 0);
	num_intersect = 0;
	cur_ray.k = 1.0;
	cur_ray.ray.origin = rtv->cam->pos;
	cur_ray.ray.dir = calculate_ray_dir(x, y, rtv);
	while (cur_ray.k > T_RAY_MIN && num_intersect < 5)
	{
		if (calculate_ray(rtv, &cur_ray) != 1)
			break ;
		num_intersect++;
	}
	return (cur_ray.color);
}
