/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbethany <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/17 21:11:19 by nbethany          #+#    #+#             */
/*   Updated: 2020/02/17 21:11:21 by nbethany         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void malloc_structures(t_rtv *rtv, int nbr[6])
{
	int i;

	if (!(rtv->cam = (t_cam*)malloc(nbr[CAM] * sizeof(t_cam))) || !(rtv->light = (t_light*)malloc(nbr[LIGHT] * sizeof(t_light))) ||
		!(rtv->sphere = (t_sphere*)malloc(nbr[SPHERE] * sizeof(t_sphere))) || !(rtv->plane = (t_plane*)malloc(nbr[PLANE] * sizeof(t_plane))) ||
		!(rtv->cylinder = (t_cylinder*)malloc(nbr[CYLINDER] * sizeof(t_cylinder))) || !(rtv->cone = (t_cone*)malloc(nbr[CONE] * sizeof(t_cone))))
		ft_error("Memory allocation error!\n", 0);

	i = -1;
	while (++i < 6)
		rtv->nbr[i] = nbr[i];
}

static void count_items(int nbr[6], char **words)
{
	if (strcmp(words[0], "CAMERA:") == 0)
		nbr[CAM]++;
	else if (strcmp(words[0], "LIGHT:") == 0)
		nbr[LIGHT]++;
	else if (strcmp(words[0], "SPHERE:") == 0)
		nbr[SPHERE]++;
	else if (strcmp(words[0], "PLANE:") == 0)
		nbr[PLANE]++;
	else if (strcmp(words[0], "CYLINDER:") == 0)
		nbr[CYLINDER]++;
	else if (strcmp(words[0], "CONE:") == 0)
		nbr[CONE]++;
	else
		ft_error("Something is wrong with items names!\n", 0);
}

static void split_string(char *line, int nbr[6])
{
	char **words;

	words = ft_strsplit(line, ' ');
	if (words[0] == NULL)
		ft_error("Invalid description file!\n", 0);
	if (words[0][0] == '/' && words[0][1] == '/')
	{
		return ;
	}
	count_items(nbr, words);
}

static int	validation2(t_rtv *rtv)
{
	char *line;
	int i;
	int nbr[6];

	rtv->fd = open(rtv->name, O_RDONLY);
	i = -1;
	while (++i < 6)
		nbr[i] = 0;
	while (get_next_line(rtv->fd, &line) == 1)
	{
		split_string(line, nbr);
		ft_strdel(&line);
	}
	ft_strdel(&line);
	if (nbr[CAM] == 0)
		ft_error("No camera was found!\n", 0);
	else if (nbr[CAM] > 1)
		ft_error("There can be only 1 camera!\n", 0);
	else if (nbr[LIGHT] == 0)
		ft_error("There must be at least 1 light source!\n", 0);
	malloc_structures(rtv, nbr);
	//close(rtv->fd); //TODO For some reason if we close a file get_next_line doesn't work. Need a fix.
	return (0);
}

static int	validation1(t_rtv *rtv)
{
	char *line;

	rtv->fd = open(rtv->name, O_RDONLY);
	if (rtv->fd < 0)
	{
		close(rtv->fd);
		return (-1);
	}
	if ((get_next_line(rtv->fd, &line) < 0))
	{
		ft_strdel(&line);
		return (-1);
	}
	ft_strdel(&line);
	//close(rtv->fd); //TODO For some reason if we close a file get_next_line doesn't work. Need a fix.
	return (0);
}

int check_color(t_color color)
{
	if (color.r > 255 || color.r < 0 || color.g > 255 || color.g < 0 || color.b > 255 || color.b < 0)
		return (0);
	return (1);
}

static void parse_camera(t_rtv *rtv, char **words, int *index)
{
	if (ft_strcmp(words[0], "CAMERA:") != 0)
		return;
	rtv->cam->pos = new_vector3(ft_atoi(words[2] + 1), ft_atoi(words[3]), ft_atoi(words[4]));
	rtv->cam->dir = new_vector3(ft_atoi(words[6] + 1), ft_atoi(words[7]), ft_atoi(words[8]));
	rtv->cam->dir = normalize(rtv->cam->dir);
	if (len_vector(rtv->cam->dir) < 0.0001f)
		ft_error("Direction of camera cannot be a null vector\n", 0);
	rtv->cam->fov = ft_atoi(words[10]);
	if (rtv->cam->fov < 0 || rtv->cam->fov > 360)
		ft_error("Incorrect FOV value, it ranges from 0 to 360\n", 0);
	(*index)++;
}

static void parse_light(t_rtv *rtv, char **words, int *index)
{
	if (ft_strcmp(words[0], "LIGHT:") != 0)
		return;
	rtv->light[*index].pos = new_vector3(ft_atoi(words[2] + 1), ft_atoi(words[3]), ft_atoi(words[4]));
	rtv->light[*index].color = set_color(ft_atoi(words[6] + 1), ft_atoi(words[7]), ft_atoi(words[8]));
	if (!check_color(rtv->light[*index].color))
		ft_error("Incorrect light color!\n", 0);
	rtv->light[*index].brightness = ft_atoi(words[10]);
	if (rtv->light[*index].brightness < 0 || rtv->light[*index].brightness > 1000)
		ft_error("Incorrect brightness value, it ranges from 0 to 1000\n", 0);
	(*index)++;
}

static void parse_items(t_rtv *rtv, char *line, int index[6])
{
	char **words;

	words = ft_strsplit(line, ' ');
	parse_camera(rtv, words, &index[0]);
	parse_light(rtv, words, &index[1]);
	parse_plane(rtv, words, &index[2]);
	parse_sphere(rtv, words, &index[3]);
	parse_cylinder(rtv, words, &index[4]);
	parse_cone(rtv, words, &index[5]);
}

static int validation3(t_rtv *rtv)
{
	char *line;
	int i;
	int index[6];

	rtv->fd = open(rtv->name, O_RDONLY);
	i = -1;
	while (++i < 6)
		index[i] = 0;
	while (get_next_line(rtv->fd, &line) == 1)
	{
		parse_items(rtv, line, index);
		ft_strdel(&line);
	}
	ft_strdel(&line);
	close(rtv->fd);
	return (0);
}

int validation (t_rtv *rtv)
{
	if (validation1(rtv) == -1 || validation2(rtv) == -1 || validation3(rtv) == -1)
		return (-1);
	else
		return (0);
}
