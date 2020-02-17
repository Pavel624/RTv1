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
	if (strcmp(words[0], "//") == 0)
	{
		return ;
	}
	count_items(nbr, words);
}

/*
** Count number of items in file
*/

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
	if (nbr[CAM] != 1)
		ft_error("There can be only 1 camera!\n", 0);
	else if (nbr[LIGHT] == 0)
		ft_error("There must be at least 1 light source!\n", 0);
	malloc_structures(rtv, nbr);
	close(rtv->fd);
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
	close(rtv->fd);
	return (0);
}

int validation (t_rtv *rtv)
{
	if (validation1(rtv) == -1 || validation2(rtv) == -1)
		return (-1);
	else
		return (1);
}
