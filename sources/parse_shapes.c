/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_shapes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbethany <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 21:55:16 by nbethany          #+#    #+#             */
/*   Updated: 2020/02/19 21:55:18 by nbethany         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void parse_plane(t_rtv *rtv, char **words, int *index)
{
	if (ft_strcmp(words[0], "PLANE:") != 0)
		return;
	rtv->plane[*index].norm = new_vector3(ft_atoi(words[2] + 1), ft_atoi(words[3]), ft_atoi(words[4]));
	rtv->plane[*index].norm = normalize(rtv->plane[*index].norm);
	if (len_vector(rtv->plane[*index].norm) < 0.0001f)
		ft_error("Direction of plane cannot be a null vector\n", 0);
	rtv->plane[*index].point = ft_atoi(words[6]);
	rtv->plane[*index].prop.diffuse = (double)ft_atoi(words[8]) / 100;
	rtv->plane[*index].prop.specular = ft_atoi(words[10]);
	if (rtv->plane[*index].prop.specular < 0 || rtv->plane[*index].prop.diffuse < 0)
		ft_error("Diffuse or specular values must be positive of zero\n", 0);
	rtv->plane[*index].prop.color = set_color(ft_atoi(words[12] + 1), ft_atoi(words[13]), ft_atoi(words[14]));
	if (!check_color(rtv->plane[*index].prop.color))
		ft_error("Incorrect plane color!\n", 0);
	(*index)++;
}

void parse_sphere(t_rtv *rtv, char **words, int *index)
{
	if (ft_strcmp(words[0], "SPHERE:") != 0)
		return;
	rtv->sphere[*index].center = new_vector3(ft_atoi(words[2] + 1), ft_atoi(words[3]), ft_atoi(words[4]));
	rtv->sphere[*index].radius = ft_atoi(words[6]);
	rtv->sphere[*index].prop.diffuse = (double)ft_atoi(words[8]) / 100;
	rtv->sphere[*index].prop.specular = ft_atoi(words[10]);
	if (rtv->sphere[*index].prop.specular < 0 || rtv->sphere[*index].prop.diffuse < 0)
		ft_error("Diffuse or specular values must be positive of zero\n", 0);
	rtv->sphere[*index].prop.color = set_color(ft_atoi(words[12] + 1), ft_atoi(words[13]), ft_atoi(words[14]));
	if (!check_color(rtv->sphere[*index].prop.color))
		ft_error("Incorrect sphere color!\n", 0);
	(*index)++;
}

void parse_cylinder(t_rtv *rtv, char **words, int *index)
{
	if (ft_strcmp(words[0], "CYLINDER:") != 0)
		return;
	rtv->cylinder[*index].dir = new_vector3(ft_atoi(words[2] + 1), ft_atoi(words[3]), ft_atoi(words[4]));
	rtv->cylinder[*index].dir = normalize(rtv->cylinder[*index].dir);
	if (len_vector(rtv->cylinder[*index].dir) < 0.0001f)
		ft_error("Direction of cylinder cannot be a null vector\n", 0);
	rtv->cylinder[*index].center = new_vector3(ft_atoi(words[6] + 1), ft_atoi(words[7]), ft_atoi(words[8]));
	rtv->cylinder[*index].radius = ft_atoi(words[10]);
	rtv->cylinder[*index].prop.diffuse = (double)ft_atoi(words[12]) / 100;
	rtv->cylinder[*index].prop.specular = ft_atoi(words[14]);
	if (rtv->cylinder[*index].prop.specular < 0 || rtv->cylinder[*index].prop.diffuse < 0)
		ft_error("Diffuse or specular values must be positive of zero\n", 0);
	rtv->cylinder[*index].prop.color = set_color(ft_atoi(words[16] + 1), ft_atoi(words[17]), ft_atoi(words[18]));
	if (!check_color(rtv->cylinder[*index].prop.color))
		ft_error("Incorrect cylinder color!\n", 0);
	(*index)++;
}

void parse_cone(t_rtv *rtv, char **words, int *index)
{
	if (ft_strcmp(words[0], "CONE:") != 0)
		return;
	rtv->cone[*index].dir = new_vector3(ft_atoi(words[2] + 1), ft_atoi(words[3]), ft_atoi(words[4]));
	rtv->cone[*index].dir = normalize(rtv->cone[*index].dir);
	if (len_vector(rtv->cone[*index].dir) < 0.0001f)
		ft_error("Direction of cone cannot be a null vector\n", 0);
	rtv->cone[*index].center = new_vector3(ft_atoi(words[6] + 1), ft_atoi(words[7]), ft_atoi(words[8]));
	rtv->cone[*index].angle = (double)ft_atoi(words[10]) * M_PI / 180;
	if (rtv->cone[*index].angle < 0 || rtv->cone[*index].angle > 45)
		ft_error("Angle of cone ranges from 0 to 45\n", 0);
	rtv->cone[*index].prop.diffuse = (double)ft_atoi(words[12]) / 100;
	rtv->cone[*index].prop.specular = ft_atoi(words[14]);
	if (rtv->cone[*index].prop.specular < 0 || rtv->cone[*index].prop.diffuse < 0)
		ft_error("Diffuse or specular values must be positive of zero\n", 0);
	rtv->cone[*index].prop.color = set_color(ft_atoi(words[16] + 1), ft_atoi(words[17]), ft_atoi(words[18]));
	if (!check_color(rtv->cone[*index].prop.color))
		ft_error("Incorrect cone color!\n", 0);
	(*index)++;
}