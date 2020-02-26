/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsatterf <rsatterf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 13:32:35 by rsatterf          #+#    #+#             */
/*   Updated: 2020/02/26 17:29:23 by rsatterf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
#include <stdio.h>

int valid1(t_rtv *rtv)
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

int valid2(t_rtv *rtv)
{
	char *line;
	int i;

	rtv->fd = open(rtv->name, O_RDONLY);
	while (get_next_line(rtv->fd, &line) > 0)
	{
		i = 0;
		while (line[i])
		{
			if (((line[i] >= 48) && (line[i] <= 57)) || (line[i] == ' ')
				|| (line[i] == '\n') || (line[i] == '-') || (line[i] == '\t')
				|| ((line[i] >= 97) && (line[i] <= 122)) || (line[i] == ')') ||
				(line[i] == '(') || (line[i] == '{') || (line[i] == '}') || (line[i] == '_'))
				i++;
			else
			{
				ft_strdel(&line);
				return (-1);
			}
		}
		ft_strdel(&line);
	}
	ft_strdel(&line);
	close(rtv->fd);
	return (0);
}

int valid_count(char *str)
{
	int i;
	int j;
	int k;

	i = 0;
	k = 0;
	j = 0;
	while (str[i] != '\0')
	{
		if ((str[i] >= 48 && str[i] <= 57) || (str[i] == '-'))
			i++;
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
	if ((j != 2) && (k != 1))
		return (-1);
	return (0);
}

int valid_count2(char *str)
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

int	data_color(char *str, t_color *vec, int k)
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
	if (((vec->r >= 0) && (vec->r <= 255)) && ((vec->g >= 0) && (vec->g <= 255)) && ((vec->b >= 0) && (vec->b <= 255)))
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

int valid_prop(t_prop *object)
{
	if ((object->specular <= 0) || (object->diffuse < 0) || (object->ambient) < 0)
		return (-1);
	else
		return (0);
}

// int valid_camera(t_cam *cam)
// {
// 	if (cam->dir.x)
// }

int valid_objects(t_rtv *rtv)
{
	char *str;
	int i;
	int k;
	int j;

	i = 0;
	while (rtv->scene[i] != NULL)
		i++;
	k = i;
	i = 0;
	while (i < k)
	{
		if (ft_strcmp(rtv->scene[i], "camera\0") == 0)
		{
			if ((i + 5) >= k)
				return (-1);
			if (ft_strcmp(rtv->scene[i + 1], "{\0") != 0 || ft_strcmp(rtv->scene[i + 5], "}\0") != 0)
				return (-1);
			if (ft_strncmp(rtv->scene[i + 2], "	pos(", 5) != 0)
				return (-1);
			if (ft_strncmp(rtv->scene[i + 3], "	dir(", 5) != 0)
				return (-1);
			if (ft_strncmp(rtv->scene[i + 4], "	fov(", 5) != 0)
				return (-1);
			str = rtv->scene[i + 2];
			if (data_vector(str, &rtv->cam[rtv->index[CAM]].pos, 5) != 0)
				return (-1);
			str = rtv->scene[i + 3];
			if (data_vector(str, &rtv->cam[rtv->index[CAM]].dir, 5) != 0)
				return (-1);
			str = rtv->scene[i + 4];
			j = 0;
			while (j != 5)
			{
				str++;
				j++;
			}
			if (valid_count2(str) != 0)
				return (-1);
			rtv->cam[rtv->index[CAM]].fov = ft_atoi(str);
			i = i + 6;
		}
		else if (ft_strcmp(rtv->scene[i], "light\0") == 0)
		{
			if ((i + 5) >= k)
				return (-1);
			if (ft_strcmp(rtv->scene[i + 1], "{\0") != 0 || ft_strcmp(rtv->scene[i + 5], "}\0") != 0)
				return (-1);
			if (ft_strncmp(rtv->scene[i + 2], "	col(", 5) != 0)
				return (-1);
			if (ft_strncmp(rtv->scene[i + 3], "	pos(", 5) != 0)
				return (-1);
			if (ft_strncmp(rtv->scene[i + 4], "	bright(", 8) != 0)
				return (-1);
			str = rtv->scene[i + 2];
			if (data_color(str, &rtv->light[rtv->index[LIGHT]].color, 5) != 0)
				return (-1);
			str = rtv->scene[i + 3];
			if (data_vector(str, &rtv->light[rtv->index[LIGHT]].pos, 5) != 0)
				return (-1);
			str = rtv->scene[i + 4];
			j = 0;
			while (j != 8)
			{
				str++;
				j++;
			}
			if (valid_count2(str) != 0)
				return (-1);
			rtv->light[rtv->index[LIGHT]].brightness = ft_atoi(str);
			if ((rtv->light[rtv->index[LIGHT]].brightness < 0) || (rtv->light[rtv->index[LIGHT]].brightness > 1000)) // check!
				return (-1);
			rtv->index[LIGHT]++;
			i = i + 6;
		}
		else if (ft_strcmp(rtv->scene[i], "plane\0") == 0)
		{
			if ((i + 7) >= k)
				return (-1);
			if (ft_strcmp(rtv->scene[i + 1], "{\0") != 0 || ft_strcmp(rtv->scene[i + 7], "}\0") != 0)
				return (-1);
			if (ft_strncmp(rtv->scene[i + 2], "	col(", 5) != 0)
				return (-1);
			if (ft_strncmp(rtv->scene[i + 3], "	norm(", 6) != 0)
				return (-1);
			if (ft_strncmp(rtv->scene[i + 4], "	point(", 7) != 0)
				return (-1);
			if (ft_strncmp(rtv->scene[i + 5], "	ambient(", 9) != 0)
				return (-1);
			if (ft_strncmp(rtv->scene[i + 6], "	specular(", 10) != 0)
				return (-1);
			str = rtv->scene[i + 2];
			if (data_color(str, &rtv->plane[rtv->index[PLANE]].prop.color, 5) != 0)
				return (-1);
			str = rtv->scene[i + 3];
			if (data_vector(str, &rtv->plane[rtv->index[PLANE]].norm, 6) != 0)
				return (-1);
			if ((rtv->plane[rtv->index[PLANE]].norm.x == 0) && (rtv->plane[rtv->index[PLANE]].norm.y == 0) && (rtv->plane[rtv->index[PLANE]].norm.z == 0)) // check!
				return (-1);
			str = rtv->scene[i + 4];
			j = 0;
			while (j != 7)
			{
				str++;
				j++;
			}
			if (valid_count2(str) != 0)
				return (-1);
			rtv->plane[rtv->index[PLANE]].point = ft_atoi(str);
			str = rtv->scene[i + 5];
			j = 0;
			while (j != 9)
			{
				str++;
				j++;
			}
			if (valid_count2(str) != 0)
				return (-1);
			rtv->plane[rtv->index[PLANE]].prop.ambient = ft_atoi(str);
			str = rtv->scene[i + 6];
			j = 0;
			while (j != 10)
			{
				str++;
				j++;
			}
			if (valid_count2(str) != 0)
				return (-1);
			rtv->plane[rtv->index[PLANE]].prop.specular = ft_atoi(str);
			rtv->plane[rtv->index[PLANE]].prop.diffuse = 0;
			if (valid_prop(&rtv->plane[rtv->index[PLANE]].prop) != 0)
				return (-1);
			i = i + 8;
			rtv->index[PLANE]++;
		}
		else if (ft_strcmp(rtv->scene[i], "sphere\0") == 0)
		{
			if ((i + 7) >= k)
				return (-1);
			if (ft_strcmp(rtv->scene[i + 1], "{\0") != 0 || ft_strcmp(rtv->scene[i + 7], "}\0") != 0)
				return (-1);
			if (ft_strncmp(rtv->scene[i + 2], "	col(", 5) != 0)
				return (-1);
			if (ft_strncmp(rtv->scene[i + 3], "	center(", 8) != 0)
				return (-1);
			if (ft_strncmp(rtv->scene[i + 4], "	radius(", 8) != 0)
				return (-1);
			if (ft_strncmp(rtv->scene[i + 5], "	diffuse(", 9) != 0)
				return (-1);
			if (ft_strncmp(rtv->scene[i + 6], "	specular(", 10) != 0)
				return (-1);
			str = rtv->scene[i + 2];
			if (data_color(str, &rtv->sphere[rtv->index[SPHERE]].prop.color, 5) != 0)
				return (-1);
			str = rtv->scene[i + 3];
			if (data_vector(str, &rtv->sphere[rtv->index[SPHERE]].center, 8) != 0)
				return (-1);
			str = rtv->scene[i + 4];
			j = 0;
			while (j != 8)
			{
				str++;
				j++;
			}
			if (valid_count2(str) != 0)
				return (-1);
			rtv->sphere[rtv->index[SPHERE]].radius = ft_atoi(str);
			if (rtv->sphere[rtv->index[SPHERE]].radius <= 0) // check!
				return (-1);
			str = rtv->scene[i + 5];
			j = 0;
			while (j != 9)
			{
				str++;
				j++;
			}
			if (valid_count2(str) != 0)
				return (-1);
			rtv->sphere[rtv->index[SPHERE]].prop.diffuse = ft_atoi(str);
			str = rtv->scene[i + 6];
			j = 0;
			while (j != 10)
			{
				str++;
				j++;
			}
			if (valid_count2(str) != 0)
				return (-1);
			rtv->sphere[rtv->index[SPHERE]].prop.specular = ft_atoi(str);
			rtv->sphere[rtv->index[SPHERE]].prop.ambient = 0;
			if (valid_prop(&rtv->plane[rtv->index[SPHERE]].prop) != 0)
				return (-1);
			i = i + 8;
			rtv->index[SPHERE]++;
		}
		else if (ft_strcmp(rtv->scene[i], "cylinder\0") == 0)
		{
			if ((i + 8) >= k)
				return (-1);
			if (ft_strcmp(rtv->scene[i + 1], "{\0") != 0 || ft_strcmp(rtv->scene[i + 8], "}\0") != 0)
				return (-1);
			if (ft_strncmp(rtv->scene[i + 2], "	col(", 5) != 0)
				return (-1);
			if (ft_strncmp(rtv->scene[i + 3], "	dir(", 5) != 0)
				return (-1);
			if (ft_strncmp(rtv->scene[i + 4], "	center(", 8) != 0)
				return (-1);
			if (ft_strncmp(rtv->scene[i + 5], "	radius(", 8) != 0)
				return (-1);
			if (ft_strncmp(rtv->scene[i + 6], "	diffuse(", 9) != 0)
				return (-1);
			if (ft_strncmp(rtv->scene[i + 7], "	specular(", 10) != 0)
				return (-1);
			str = rtv->scene[i + 2];
			if (data_color(str, &rtv->cylinder[rtv->index[CYLINDER]].prop.color, 5) != 0)
				return (-1);
			str = rtv->scene[i + 3];
			if (data_vector(str, &rtv->cylinder[rtv->index[CYLINDER]].dir, 5) != 0)
				return (-1);
			str = rtv->scene[i + 4];
			if (data_vector(str, &rtv->cylinder[rtv->index[CYLINDER]].center, 8) != 0)
				return (-1);
			str = rtv->scene[i + 5];
			j = 0;
			while (j != 8)
			{
				str++;
				j++;
			}
			if (valid_count2(str) != 0)
				return (-1);
			rtv->cylinder[rtv->index[CYLINDER]].radius = ft_atoi(str);
			str = rtv->scene[i + 6];
			j = 0;
			while (j != 9)
			{
				str++;
				j++;
			}
			if (valid_count2(str) != 0)
				return (-1);
			rtv->cylinder[rtv->index[CYLINDER]].prop.diffuse = ft_atoi(str);
			str = rtv->scene[i + 7];
			j = 0;
			while (j != 10)
			{
				str++;
				j++;
			}
			if (valid_count2(str) != 0)
				return (-1);
			rtv->cylinder[rtv->index[CYLINDER]].prop.specular = ft_atoi(str);
			rtv->cylinder[rtv->index[CYLINDER]].prop.ambient = 0;
			if (valid_prop(&rtv->plane[rtv->index[CYLINDER]].prop) != 0)
				return (-1);
			i = i + 9;
			rtv->index[CYLINDER]++;
		}
		else if (ft_strcmp(rtv->scene[i], "cone\0") == 0)
		{
			if ((i + 8) >= k)
				return (-1);
			if (ft_strcmp(rtv->scene[i + 1], "{\0") != 0 || ft_strcmp(rtv->scene[i + 8], "}\0") != 0)
				return (-1);
			if (ft_strncmp(rtv->scene[i + 2], "	col(", 5) != 0)
				return (-1);
			if (ft_strncmp(rtv->scene[i + 3], "	dir(", 5) != 0)
				return (-1);
			if (ft_strncmp(rtv->scene[i + 4], "	center(", 8) != 0)
				return (-1);
			if (ft_strncmp(rtv->scene[i + 5], "	angle(", 7) != 0)
				return (-1);
			if (ft_strncmp(rtv->scene[i + 6], "	diffuse(", 9) != 0)
				return (-1);
			if (ft_strncmp(rtv->scene[i + 7], "	specular(", 10) != 0)
				return (-1);
			str = rtv->scene[i + 2];
			if (data_color(str, &rtv->cone[rtv->index[CONE]].prop.color, 5) != 0)
				return (-1);
			str = rtv->scene[i + 3];
			if (data_vector(str, &rtv->cone[rtv->index[CONE]].dir, 5) != 0)
				return (-1);
			str = rtv->scene[i + 4];
			if (data_vector(str, &rtv->cone[rtv->index[CONE]].center, 8) != 0)
				return (-1);
			str = rtv->scene[i + 5];
			j = 0;
			while (j != 7)
			{
				str++;
				j++;
			}
			if (valid_count2(str) != 0)
				return (-1);
			rtv->cone[rtv->index[CONE]].angle = ft_atoi(str);
			if ((rtv->cone[rtv->index[CONE]].angle < 0) || (rtv->cone[rtv->index[CONE]].angle > 90)) // check!
				return (-1);
			str = rtv->scene[i + 6];
			j = 0;
			while (j != 9)
			{
				str++;
				j++;
			}
			if (valid_count2(str) != 0)
				return (-1);
			rtv->cone[rtv->index[CONE]].prop.diffuse = ft_atoi(str);
			str = rtv->scene[i + 7];
			j = 0;
			while (j != 10)
			{
				str++;
				j++;
			}
			if (valid_count2(str) != 0)
				return (-1);
			rtv->cone[rtv->index[CONE]].prop.specular = ft_atoi(str);
			rtv->cone[rtv->index[CONE]].prop.ambient = 0;
			if (valid_prop(&rtv->plane[rtv->index[CONE]].prop) != 0)
				return (-1);
			i = i + 9;
			rtv->index[CONE]++;
		}
	}
	return (0);
}


void print_m(t_rtv *rtv)
{
	int i;

	i = 0;
	while (rtv->scene[i])
	{
		printf("%s;", rtv->scene[i]);
		i++;
	}
}

char		*ft_strjoin_2(char *s1, char *s2)
{
	char	*snew;
	size_t	len;

	if (!s1 || !s2)
		return (NULL);
	len = ft_strlen(s1) + ft_strlen(s2);
	snew = (char *)malloc(sizeof(*snew) * (len + 1));
	if (!snew)
		return (NULL);
	ft_strcpy(snew, s1);
	ft_strcat(snew, s2);
	ft_strdel(&s1);
	return (snew);
}

void render2(t_rtv *rtv)
{
	char *line;
	char *str;

	rtv->buf = ft_strnew(1);
	rtv->fd = open(rtv->name, O_RDONLY);
	while (get_next_line(rtv->fd, &line) > 0)
	{
		str = ft_strjoin(line, "\n");
		rtv->buf = ft_strjoin_2(rtv->buf, str);
		ft_strdel(&str);
		ft_strdel(&line);
	}
	rtv->scene = ft_strsplit(rtv->buf, '\n');
	ft_strdel(&line);
	ft_strdel(&str);
	ft_strdel(&rtv->buf);
}

int count_items(t_rtv *rtv)
{
	int i;

	i = 0;
	while (rtv->scene[i])
	{
		if (ft_strcmp(rtv->scene[i], "camera\0") == 0)
			rtv->nbr[CAM]++;
		else if (ft_strcmp(rtv->scene[i], "light\0") == 0)
			rtv->nbr[LIGHT]++;
		else if (ft_strcmp(rtv->scene[i], "sphere\0") == 0)
			rtv->nbr[SPHERE]++;
		else if (ft_strcmp(rtv->scene[i], "plane\0") == 0)
			rtv->nbr[PLANE]++;
		else if (ft_strcmp(rtv->scene[i], "cylinder\0") == 0)
			rtv->nbr[CYLINDER]++;
		else if (ft_strcmp(rtv->scene[i], "cone\0") == 0)
			rtv->nbr[CONE]++;
		i++;
	}
	if ((rtv->nbr[CAM] != 1) || (rtv->nbr[LIGHT] == 0))
		return (-1);
	return (0);
}

void malloc_structures(t_rtv *rtv)
{
	if (!(rtv->cam = (t_cam*)malloc(rtv->nbr[CAM] * sizeof(t_cam))) || !(rtv->light = (t_light*)malloc(rtv->nbr[LIGHT] * sizeof(t_light))) ||
		!(rtv->sphere = (t_sphere*)malloc(rtv->nbr[SPHERE] * sizeof(t_sphere))) || !(rtv->plane = (t_plane*)malloc(rtv->nbr[PLANE] * sizeof(t_plane))) ||
		!(rtv->cylinder = (t_cylinder*)malloc(rtv->nbr[CYLINDER] * sizeof(t_cylinder))) || !(rtv->cone = (t_cone*)malloc(rtv->nbr[CONE] * sizeof(t_cone))))
		ft_error("Memory allocation error!\n", 0);
}

int valid(t_rtv *rtv)
{
	if ((valid1(rtv) != 0))     // norm
	{
		write(1, "one\n", 4);
		return (-1);
	}
	else if ((valid2(rtv) != 0)) // norm
	{
		write(1, "two\n", 4);
		return (-1);
	}
	render2(rtv);  // norm

	if (count_items(rtv) != 0) // if no content or scene?
	{
		write(1, "three\n", 6);
		ft_strdel(rtv->scene);
		return (-1);
	}
	malloc_structures(rtv);
	if (valid_objects(rtv) != 0) // norm
	{
		write(1, "five\n", 5);
		return (-1);
	}
	// printf("%f\n", rtv->cam[0].pos.x);
	// printf("%f\n", rtv->cam[0].pos.y);
	// printf("%f\n", rtv->cam[0].pos.z);
	// printf("%d\n", rtv->cam[0].fov);

	// printf("%f\n", rtv->light[0].color.r);
	// printf("%f\n", rtv->light[0].color.g);
	// printf("%f\n", rtv->light[0].color.b);
	// printf("%d\n", rtv->light[0].brightness);

	// printf("%f\n", rtv->light[1].color.r);
	// printf("%f\n", rtv->light[1].color.g);
	// printf("%f\n", rtv->light[1].color.b);
	// printf("%d\n", rtv->light[1].brightness);

	// printf("%f\n", rtv->sphere[0].prop.color.r);
	// printf("%f\n", rtv->sphere[0].prop.color.g);
	// printf("%f\n", rtv->sphere[0].prop.color.b);
	// printf("%d\n", rtv->sphere[0].radius);

	// printf("%f\n", rtv->cylinder[0].prop.color.r);
	// printf("%f\n", rtv->cylinder[0].prop.color.g);
	// printf("%f\n", rtv->cylinder[0].prop.color.b);
	// printf("%d\n", rtv->cylinder[0].radius);
	// printf("%f\n", rtv->cylinder[0].dir.x);
	// printf("%f\n", rtv->cylinder[0].dir.y);
	// printf("%f\n", rtv->cylinder[0].dir.z);
	// printf("%d\n", rtv->cylinder[0].prop.specular);

	printf("%f\n", rtv->cone[0].prop.color.r);
	printf("%f\n", rtv->cone[0].prop.color.g);
	printf("%f\n", rtv->cone[0].prop.color.b);
	printf("%f\n", rtv->cone[0].angle);
	printf("%f\n", rtv->cone[0].center.x);
	printf("%f\n", rtv->cone[0].center.y);
	printf("%f\n", rtv->cone[0].center.z);
	printf("%d\n", rtv->cone[0].prop.specular);

	return (0);
}


static	int		close_app(t_rtv *rtv)
{
	free(rtv);
	exit(0);
}

void	ft_error(char *msg, int i)
{
	ft_putstr(msg);
	exit(i);
}

static	void	init(t_rtv *rtv)
{
	t_image *image;

	image = &rtv->image;
	rtv->mlx = mlx_init();
	rtv->window = mlx_new_window(rtv->mlx, WIDTH, HEIGHT, "RTv1");
	image->image = mlx_new_image(rtv->mlx, WIDTH, HEIGHT);
	image->ptr = mlx_get_data_addr(image->image, &image->bpp,
		&image->line_s, &image->endian);
	image->bpp /= 8;
}

void	img_pixel_put_one(t_rtv *rtv, int x, int y, t_color color)
{
	if (x > 0 && x < WIDTH && y > 0 && y < HEIGHT)
	{
		rtv->image.ptr[(WIDTH * y + x) * rtv->image.bpp + 2] = (char) fmin(color.r * 255.0f, 255.0f);
		rtv->image.ptr[(WIDTH * y + x) * rtv->image.bpp + 1] = (char) fmin(color.g * 255.0f, 255.0f);
		rtv->image.ptr[(WIDTH * y + x) * rtv->image.bpp] = (char) fmin(color.b * 255.0f, 255.0f);

	}
}

void scene1(t_rtv *rtv)
{
	int i = 0;
	while (i++ < 6)
		rtv->nbr[i] = 0;
	rtv->nbr[SPHERE] = 9;
	rtv->nbr[CYLINDER] = 4;
	rtv->nbr[CAM] = 1; //there can be only 1 cam
	rtv->nbr[LIGHT] = 2;
	rtv->nbr[PLANE] = 3;
	rtv->nbr[CONE] = 1;

	rtv->sphere = malloc(rtv->nbr[SPHERE] * sizeof(t_sphere));
	rtv->cylinder = malloc(rtv->nbr[CYLINDER] * sizeof(t_cylinder));
	rtv->light = malloc(rtv->nbr[LIGHT] * sizeof(t_light));
	rtv->cam = malloc(rtv->nbr[CAM] * sizeof(t_cam));
	rtv->plane = malloc(rtv->nbr[PLANE] * sizeof(t_plane));
	rtv->cone = malloc(rtv->nbr[CONE] * sizeof(t_cone));

	rtv->cam->pos = new_vector3(0, 0, 170);
	rtv->cam->dir = normalize(new_vector3(0, 0, -1));
	rtv->cam->fov = 60;

	rtv->plane[0] = new_plane(new_vector3 (0, 1, 0), 30);
	rtv->plane[0].prop.diffuse = 0; // any reflection from a plane will result in some strange results
	rtv->plane[0].prop.specular = 200;
	rtv->plane[0].prop.color = set_color(80, 80, 80);

	rtv->plane[1] = new_plane(new_vector3 (0, 0, -1), 40);
	rtv->plane[1].prop.specular = 0;
	rtv->plane[1].prop.specular = 200;
	rtv->plane[1].prop.color = set_color(0, 80, 127);

	rtv->plane[2] = new_plane(new_vector3 (0, 1, 0), -30);
	rtv->plane[2].prop.diffuse = 0;
	rtv->plane[2].prop.specular = 200;
	rtv->plane[2].prop.color = set_color(80, 80, 80);

	rtv->light[0].pos = new_vector3(80, 20, 150);
	rtv->light[0].color = set_color(255, 255, 255);
	rtv->light[0].brightness = 50;

	rtv->light[1].pos = new_vector3(-80, 20, 150);
	rtv->light[1].color = set_color(255, 255, 255);
	rtv->light[1].brightness = 50;

	rtv->sphere[0] = new_sphere(new_vector3(-30, 30, 0), 10);
	rtv->sphere[0].prop.diffuse = 0; // FROM 0 to 1 or reflected light will produce more than a source
	rtv->sphere[0].prop.specular = 200; // light absorption value
	rtv->sphere[0].prop.color = set_color(80, 80, 80);

	rtv->sphere[1] = new_sphere(new_vector3(-30, -30, 0), 10);
	rtv->sphere[1].prop.diffuse = 0; // FROM 0 to 1 or reflected light will produce more than a source
	rtv->sphere[1].prop.specular = 200; // light absorption value
	rtv->sphere[1].prop.color = set_color(80, 80, 80);

	rtv->sphere[2] = new_sphere(new_vector3(30, -30, 0), 10);
	rtv->sphere[2].prop.diffuse = 0; // FROM 0 to 1 or reflected light will produce more than a source
	rtv->sphere[2].prop.specular = 200; // light absorption value
	rtv->sphere[2].prop.color = set_color(80, 80, 80);

	rtv->sphere[3] = new_sphere(new_vector3(30, 30, 0), 10);
	rtv->sphere[3].prop.diffuse = 0; // FROM 0 to 1 or reflected light will produce more than a source
	rtv->sphere[3].prop.specular = 200; // light absorption value
	rtv->sphere[3].prop.color = set_color(80, 80, 80);

	rtv->cylinder[0] = new_cylinder(normalize(new_vector3(0, 1, 0)), new_vector3(30, 0, 0), 6);
	rtv->cylinder[0].prop.diffuse = 0;
	rtv->cylinder[0].prop.specular = 400;
	rtv->cylinder[0].prop.color = set_color(80, 80, 80);

	rtv->cylinder[1] = new_cylinder(normalize(new_vector3(0, 1, 0)), new_vector3(-30, 0, 0), 6);
	rtv->cylinder[1].prop.diffuse = 0;
	rtv->cylinder[1].prop.specular = 400;
	rtv->cylinder[1].prop.color = set_color(80, 80, 80);

	//second row
	rtv->sphere[4] = new_sphere(new_vector3(30, 30, 70), 10);
	rtv->sphere[4].prop.diffuse = 0; // FROM 0 to 1 or reflected light will produce more than a source
	rtv->sphere[4].prop.specular = 200; // light absorption value
	rtv->sphere[4].prop.color = set_color(80, 80, 80);

	rtv->sphere[5] = new_sphere(new_vector3(-30, 30, 70), 10);
	rtv->sphere[5].prop.diffuse = 0; // FROM 0 to 1 or reflected light will produce more than a source
	rtv->sphere[5].prop.specular = 200; // light absorption value
	rtv->sphere[5].prop.color = set_color(80, 80, 80);

	rtv->sphere[6] = new_sphere(new_vector3(30, -30, 70), 10);
	rtv->sphere[6].prop.diffuse = 0; // FROM 0 to 1 or reflected light will produce more than a source
	rtv->sphere[6].prop.specular = 200; // light absorption value
	rtv->sphere[6].prop.color = set_color(80, 80, 80);

	rtv->sphere[7] =new_sphere(new_vector3(-30, -30, 70), 10);
	rtv->sphere[7].prop.diffuse = 0; // FROM 0 to 1 or reflected light will produce more than a source
	rtv->sphere[7].prop.specular = 200; // light absorption value
	rtv->sphere[7].prop.color = set_color(80, 80, 80);

	rtv->cylinder[2] = new_cylinder(normalize(new_vector3(0, 1, 0)), new_vector3(-30, 0 , 70), 6);
	rtv->cylinder[2].prop.diffuse = 0;
	rtv->cylinder[2].prop.specular = 250;
	rtv->cylinder[2].prop.color = set_color(80, 80, 80);

	rtv->cylinder[3] = new_cylinder(normalize(new_vector3(0, 1, 0)), new_vector3(30, 0, 70), 6);
	rtv->cylinder[3].prop.diffuse = 0;
	rtv->cylinder[3].prop.specular = 250;
	rtv->cylinder[3].prop.color = set_color(80, 80, 80);

	rtv->sphere[8] = new_sphere(new_vector3(0, -20, 50), 6);
	rtv->sphere[8].prop.diffuse = 0.11; // FROM 0 to 1 or reflected light will produce more than a source
	rtv->sphere[8].prop.specular = 200; // light absorption value
	rtv->sphere[8].prop.color = set_color(255, 50, 50);

}

void scene2(t_rtv *rtv)
{
	int i = 0;
	while (i++ < 6)
		rtv->nbr[i] = 0;
	rtv->nbr[SPHERE] = 1;
	rtv->nbr[CYLINDER] = 1;
	rtv->nbr[CAM] = 1; //there can be only 1 cam
	rtv->nbr[LIGHT] = 1;
	rtv->nbr[PLANE] = 2;
	rtv->nbr[CONE] = 0;

	rtv->sphere = malloc(rtv->nbr[SPHERE] * sizeof(t_sphere));
	rtv->cylinder = malloc(rtv->nbr[CYLINDER] * sizeof(t_cylinder));
	rtv->light = malloc(rtv->nbr[LIGHT] * sizeof(t_light));
	rtv->cam = malloc(rtv->nbr[CAM] * sizeof(t_cam));
	rtv->plane = malloc(rtv->nbr[PLANE] * sizeof(t_plane));
	rtv->cone = malloc(rtv->nbr[CONE] * sizeof(t_cone));

	rtv->plane[0] = new_plane(new_vector3 (0, 1, 0), -200);
	rtv->plane[0].prop.diffuse = 0; // any reflection from a plane will result in some strange results
	rtv->plane[0].prop.specular = 200;
	rtv->plane[0].prop.color = set_color(80, 80, 80);

	rtv->plane[1] = new_plane(new_vector3 (0, 0, 1), 200);
	rtv->plane[1].prop.diffuse = 0;
	rtv->plane[1].prop.specular = 200;
	rtv->plane[1].prop.color = set_color(0, 80, 127);

	rtv->light[0].pos = new_vector3(100, 50, -300);
	rtv->light[0].color = set_color(255, 255, 255);
	rtv->light[0].brightness = 200;

	rtv->cam->pos = new_vector3(0, 0, -500);
	rtv->cam->dir = normalize (new_vector3(0, 0, 1));
	rtv->cam->fov = 90;

	rtv->sphere[0] = new_sphere(new_vector3(-50, -140, -100), 60);
	rtv->sphere[0].prop.diffuse = 0; // FROM 0 to 1 or reflected light will produce more than a source
	rtv->sphere[0].prop.specular = 200; // light absorption value
	rtv->sphere[0].prop.color = set_color(255, 50, 50);

	rtv->cylinder[0] = new_cylinder(normalize(new_vector3(1, 1, 0)), new_vector3(180, 300, 70), 90);
	rtv->cylinder[0].prop.diffuse = 0;
	rtv->cylinder[0].prop.specular = 400;
	rtv->cylinder[0].prop.color = set_color(80, 255, 80);

	rtv->cone[0] = new_cone(normalize(new_vector3(0, 1, 0)), new_vector3(0, 0, 15), 0.1);
	rtv->cone[0].prop.diffuse = 0;
	rtv->cone[0].prop.specular = 200;
	rtv->cone[0].prop.color = set_color(255, 0, 255);

}

void init_shapes(t_rtv *rtv)
{
	int i = 0;
	while (i++ < 6)
		rtv->nbr[i] = 0;
	rtv->nbr[SPHERE] = 3;
	rtv->nbr[CYLINDER] = 2;
	rtv->nbr[CAM] = 1; //there can be only 1 cam
	rtv->nbr[LIGHT] = 2;
	rtv->nbr[PLANE] = 5;
	rtv->nbr[CONE] = 1;

	rtv->sphere = malloc(rtv->nbr[SPHERE] * sizeof(t_sphere));
	rtv->cylinder = malloc(rtv->nbr[CYLINDER] * sizeof(t_cylinder));
	rtv->light = malloc(rtv->nbr[LIGHT] * sizeof(t_light));
	rtv->cam = malloc(rtv->nbr[CAM] * sizeof(t_cam));
	rtv->plane = malloc(rtv->nbr[PLANE] * sizeof(t_plane));
	rtv->cone = malloc(rtv->nbr[CONE] * sizeof(t_cone));

	rtv->plane[0] = new_plane(new_vector3 (0, 1, 0), -300);
	rtv->plane[0].prop.diffuse = 0; // any reflection from a plane will result in some strange results
	rtv->plane[0].prop.specular = 200;
	rtv->plane[0].prop.color = set_color(255, 0, 0);

	rtv->plane[1] = new_plane(new_vector3 (0, 0, 1), 300);
	rtv->plane[1].prop.diffuse = 0;
	rtv->plane[1].prop.specular = 200;
	rtv->plane[1].prop.color = set_color(0, 255, 0);

	rtv->plane[2] = new_plane(new_vector3 (1, 0, 0), -400);
	rtv->plane[2].prop.diffuse = 0;
	rtv->plane[2].prop.specular = 200;
	rtv->plane[2].prop.color = set_color(0, 255, 0);

	rtv->plane[3] = new_plane(new_vector3 (1, 0, 0), 400);
	rtv->plane[3].prop.diffuse = 0;
	rtv->plane[3].prop.specular = 200;
	rtv->plane[3].prop.color = set_color(0, 255, 0);

	rtv->plane[4] = new_plane(new_vector3 (0, 1, 0), 300);
	rtv->plane[4].prop.diffuse = 0;
	rtv->plane[4].prop.specular = 200;
	rtv->plane[4].prop.color = set_color(0, 255, 0);

	rtv->light[0].pos = new_vector3(0, 250, 200);
	rtv->light[0].color = set_color(255, 255, 255);
	rtv->light[0].color = set_color(255, 255, 255);

	rtv->cam->pos = new_vector3(0, 0, -1);
	rtv->cam->dir = new_vector3(0, 0, 1);

	rtv->sphere[0] = new_sphere(new_vector3(-200, -140, 200), 100);
	rtv->sphere[0].prop.diffuse = 1; // FROM 0 to 1 or reflected light will produce more than a source
	rtv->sphere[0].prop.specular = 200; // light absorption value
	rtv->sphere[0].prop.color = set_color(255, 127, 0);

	rtv->sphere[1] = new_sphere(new_vector3(200, -120, 150), 100);
	rtv->sphere[1].prop.diffuse = 1; // FROM 0 to 1 or reflected light will produce more than a source
	rtv->sphere[1].prop.specular = 200; // light absorption value
	rtv->sphere[1].prop.color = set_color(255, 255, 0);

	rtv->cylinder[0] = new_cylinder(normalize(new_vector3(0, 1, 0)), new_vector3(250, 0, 150), 30);
	rtv->cylinder[0].prop.specular = 250;
	rtv->cylinder[0].prop.color = set_color(0, 127, 255);

	t_vector3 center = new_vector3(4, 0, 15);
	rtv->sphere[0] = new_sphere(center, 4);
	rtv->sphere[0].prop.specular = 200; // light absorption value
	rtv->sphere[0].prop.color = set_color(255, 127, 0);

    rtv->cone[0] = new_cone(normalize(new_vector3(0, 1, 0)), new_vector3(0, 0, 15), 0.1);
	rtv->cone[0].prop.diffuse = 0;
	rtv->cone[0].prop.specular = 200;
	rtv->cone[0].prop.color = set_color(255, 0, 255);
}

void test_scene(t_rtv *rtv)
{
	int i = 0;
	while (i++ < 6)
		rtv->nbr[i] = 0;
	rtv->nbr[SPHERE] = 1;
	rtv->nbr[CYLINDER] = 0;
	rtv->nbr[CAM] = 1; //there can be only 1 cam
	rtv->nbr[LIGHT] = 1;
	rtv->nbr[PLANE] = 0;
	rtv->nbr[CONE] = 0;

	rtv->sphere = malloc(rtv->nbr[SPHERE] * sizeof(t_sphere));
	rtv->cylinder = malloc(rtv->nbr[CYLINDER] * sizeof(t_cylinder));
	rtv->light = malloc(rtv->nbr[LIGHT] * sizeof(t_light));
	rtv->cam = malloc(rtv->nbr[CAM] * sizeof(t_cam));
	rtv->plane = malloc(rtv->nbr[PLANE] * sizeof(t_plane));
	rtv->cone = malloc(rtv->nbr[CONE] * sizeof(t_cone));

	rtv->light[0].pos = new_vector3(-80, 20, 40);
	rtv->light[0].color = set_color(255, 255, 255);
	rtv->light[0].brightness = 50;

//	rtv->light[1].pos = new_vector3(-80, 20, 150);
//	rtv->light[1].color = set_color(255, 255, 255);
//	rtv->light[1].brightness = 500;

	rtv->sphere[0] = new_sphere(new_vector3(0, 0, 50), 6);
	rtv->sphere[0].prop.diffuse = 0; // FROM 0 to 1 or reflected light will produce more than a source
	rtv->sphere[0].prop.specular = 150; // light absorption value
	rtv->sphere[0].prop.color = set_color(255, 127, 0);

	rtv->cam->pos = new_vector3(0, 0, 0);
	rtv->cam->dir = new_vector3(0, 0, 1);
	rtv->cam->fov = 60;

}


int draw(t_rtv *rtv)
{
	int 		x;
	int			y;
	//int Sx;
	//int Sy;
	int Cw;
	int Ch;
	t_color		color;

	//Cw = WIDTH / 2;
	//Ch = HEIGHT / 2;
	Cw = WIDTH;
	Ch = HEIGHT;
	//x = -Cw;
	x = 0;
	while (x < Cw)
	{
		//y = -Ch;
		y = 0;
		while (y < Ch)
		{
			//Sx = Cw + x;
			//Sy = Ch - y;
			color = calculate_color((t_rtv*)rtv, x , y);
			img_pixel_put_one((t_rtv*)rtv, x , y, color);
			y++;
		}
		x++;
	}
	mlx_put_image_to_window(rtv->mlx, rtv->window, rtv->image.image, 0, 0);
	return (0);
}

int				main(int argc, char **argv)
{
	t_rtv *rtv;

	if (argc > 2)
		ft_error("Too many parameters\n", 0);
	else if (argc == 1)
		ft_error("Use scene from scenes\n", 0);
	if (!(rtv = (t_rtv *)malloc(sizeof(t_rtv))))
		ft_error("Can't allocate enough memory for the structure\n", 0);
	rtv->name = argv[1];
	//init_shapes(rtv);
	//scene1(rtv);
	//scene2(rtv);
	//test_scene(rtv);
	if (valid(rtv) != 0)
	{
		free(rtv);
		ft_error("Something is wrong with scene input\n", 0);
	}
	//scene2(rtv);
	init(rtv);
	mlx_expose_hook(rtv->window, draw, rtv);
	mlx_hook(rtv->window, 3, 1L << 1, key_release, rtv);
	mlx_hook(rtv->window, 17, 1L << 17, close_app, rtv);
	mlx_loop(rtv->mlx);
	return (0);
}
