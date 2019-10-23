/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsatterf <rsatterf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 13:32:35 by rsatterf          #+#    #+#             */
/*   Updated: 2019/10/23 15:02:06 by rsatterf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
#include <stdio.h>

/*int valid1(t_rtv *rtv)
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
			if (((line[i] >= 48) && (line[i] <= 57)) || (line[i] == ' ') ||
				(line[i] == '\n') || (line[i] == '-') || (line[i] == '\t')
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

int count(t_rtv *rtv)
{
	char *line;
	int i;
	int j;

	j = 0;
	rtv->fd = open(rtv->name, O_RDONLY);
	while (get_next_line(rtv->fd, &line) > 0)
	{
		i = 0;
		while (line[i])
		{
			if (line[i] == '\n')
				j++;
		}
		ft_strdel(&line);
	}
	ft_strdel(&line);
	close(rtv->fd);
	return (j);
}

int ft_line_count(char *line)
{
	int i;

	i = 0;
	while ((line[i] != '\n') && (line[i] != '\0'))
		i++;
	return (i);
}

int valid_scene(t_rtv *rtv)
{
	int i;

	if (ft_strcmp(rtv->scene[0], "scene\0") != 0)
	{
		printf("%s\n", rtv->scene[0]);
		return (-1);
	}
	else if (ft_strcmp(rtv->scene[1], "{\0") != 0)
	{
		printf("%s\n", rtv->scene[1]);
		return (-1);
	}
	else if (ft_strcmp(rtv->scene[4], "}\0") != 0)
	{
		printf("%s\n", rtv->scene[4]);
		return (-1);
	}
	else if (ft_strcmp(rtv->scene[5], "content\0") != 0)
	{
		printf("%s\n", rtv->scene[5]);
		return (-1);
	}
	else if (ft_strcmp(rtv->scene[6], "{\0") != 0)
	{
		printf("%s\n", rtv->scene[6]);
		return (-1);
	}
	i = 0;
	while (rtv->scene[i] != NULL)
		i++;
	if (ft_strcmp(rtv->scene[i - 1], "}\0") != 0)
	{
		printf("%s\n", rtv->scene[i - 1]);
		return (-1);
	}
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

//int valid_scene2(t_rtv *rtv)
//{
//	char *str;
//	int i;
//
//	rtv->cam.pos = (t_vector3*)malloc(sizeof(t_vector3));
//	rtv->cam.dir = (t_vector3*)malloc(sizeof(t_vector3));
//	if (ft_strncmp(rtv->scene[2], "	cam_pos(", 9) != 0)
//		return (-1);
//	str = rtv->scene[2];
//	i = 0;
//	while(i != 9)
//	{
//		str++;
//		i++;
//	}
//	if (valid_count(str) != 0)
//		return (-1);
//	rtv->cam.pos->x = ft_atoi(str);
//	while (*str != ' ')
//		str++;
//	str++;
//	rtv->cam.pos->y = ft_atoi(str);
//	while (*str != ' ')
//		str++;
//	rtv->cam.pos->z = ft_atoi(str);
//	if (ft_strncmp(rtv->scene[3], "	cam_dir(", 9) != 0)
//		return (-1);
//	str = rtv->scene[3];
//	i = 0;
//	while(i != 9)
//	{
//		str++;
//		i++;
//	}
//	if (valid_count(str) != 0)
//		return (-1);
//	rtv->cam.dir->x = ft_atoi(str);
//	while (*str != ' ')
//		str++;
//	str++;
//	rtv->cam.dir->y = ft_atoi(str);
//	while (*str != ' ')
//		str++;
//	rtv->cam.dir->z = ft_atoi(str);
//	return(0);
//}
//
//void init_light(t_rtv *rtv)
//{
//	rtv->light = (t_light *)malloc(sizeof(t_light));
//	rtv->light->color = (t_vector3*)malloc(sizeof(t_vector3));
//	rtv->light->pos = (t_vector3*)malloc(sizeof(t_vector3));
//}
//
//void init_plane(t_rtv *rtv)
//{
//	rtv->plane = (t_plane *)malloc(sizeof(t_plane));
//	rtv->plane->color = (t_vector3*)malloc(sizeof(t_vector3));
//	rtv->plane->pos = (t_vector3*)malloc(sizeof(t_vector3));
//	rtv->plane->rot = (t_vector3*)malloc(sizeof(t_vector3));
//}
//
//void init_sphere(t_rtv *rtv)
//{
//	rtv->sphere = (t_sphere *)malloc(sizeof(t_sphere));
//	rtv->sphere->color = (t_vector3*)malloc(sizeof(t_vector3));
//	rtv->sphere->center = (t_vector3*)malloc(sizeof(t_vector3));
//}

int	data(char *str, t_vector3 vec, int k)
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
	vec.x = ft_atoi(str);
	while (*str != ' ')
		str++;
	str++;
	vec.y = ft_atoi(str);
	while (*str != ' ')
		str++;
	vec.z = ft_atoi(str);
	return (0);
}

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
	i = 7;
	while (i != k - 1)
	{
		if (ft_strcmp(rtv->scene[i], "	object(light)\0") == 0)
		{
			//if ((i + 4) >= k)
				//return (-1);
			if (ft_strcmp(rtv->scene[i + 1], "	{\0") != 0 || ft_strcmp(rtv->scene[i + 4], "	}\0") != 0)
				return (-1);
			//init_light(rtv);
			if (ft_strncmp(rtv->scene[i + 2], "		col(", 6) != 0)
				return (-1);
			str = rtv->scene[i + 2];
			//if (data(str, rtv->light.intensity, 6) != 0)
			//	return (-1);
			if (ft_strncmp(rtv->scene[i + 3], "		pos(", 6) != 0)
				return (-1);
			str = rtv->scene[i + 3];
			//if (data(str, rtv->light.pos, 6) != 0)
			//	return (-1);
			i = i + 5;
		}
		else if (ft_strcmp(rtv->scene[i], "	object(plane)\0") == 0)
		{
			//if ((i + 4) >= k)
				//return (-1);
			if (ft_strcmp(rtv->scene[i + 1], "	{\0") != 0 || ft_strcmp(rtv->scene[i + 5], "	}\0") != 0)
				return (-1);
			//init_plane(rtv);
			if (ft_strncmp(rtv->scene[i + 2], "		col(", 6) != 0)
				return (-1);
			str = rtv->scene[i + 2];
			//if (data(str, rtv->plane->color, 6) != 0)
			//	return (-1);
			if (ft_strncmp(rtv->scene[i + 3], "		pos(", 6) != 0)
				return (-1);
			str = rtv->scene[i + 3];
			if (data(str, rtv->plane->pos, 6) != 0)
				return (-1);
			if (ft_strncmp(rtv->scene[i + 4], "		rot(", 6) != 0)
				return (-1);
			str = rtv->scene[i + 4];
			if (data(str, rtv->plane->rot, 6) != 0)
				return (-1);
			i = i + 6;
		}
		else if (ft_strcmp(rtv->scene[i], "	object(sphere)\0") == 0)
		{
			//if ((i + 4) >= k)
				//return (-1);
			if (ft_strcmp(rtv->scene[i + 1], "	{\0") != 0 || ft_strcmp(rtv->scene[i + 5], "	}\0") != 0)
				return (-1);
			//init_sphere(rtv);
			if (ft_strncmp(rtv->scene[i + 2], "		col(", 6) != 0)
				return (-1);
			str = rtv->scene[i + 2];
			//if (data(str, rtv->sphere->color, 6) != 0)
			//	return (-1);
			if (ft_strncmp(rtv->scene[i + 3], "		pos(", 6) != 0)
				return (-1);
			str = rtv->scene[i + 3];
			if (data(str, rtv->sphere->center, 6) != 0)
				return (-1);
			if (ft_strncmp(rtv->scene[i + 4], "		size(", 7) != 0)
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
			rtv->sphere->radius = ft_atoi(str);
			i = i + 6;
		}
	}
	return (0);
}

void render2(t_rtv *rtv)
{
	char *line;

	rtv->buf = ft_strnew(1);
	rtv->fd = open(rtv->name, O_RDONLY);
	while (get_next_line(rtv->fd, &line) > 0)
		rtv->buf = ft_strjoin(rtv->buf, (ft_strjoin(line, "\n")));
	rtv->scene = ft_strsplit(rtv->buf, '\n');
}

//int render1(t_rtv *rtv)
//{
//	int		a[3];
//	char	*line;
//	char	**tab;
//
//	rtv->scene = (char **)malloc(sizeof(char *) * ());
//	a[1] = 0;
//	wolf->fd = open(wolf->name, O_RDONLY);
//	while ((a[0] = get_next_line(wolf->fd, &line)) > 0)
//	{
//		tab = ft_strsplit(line, ' ');
//		wolf->map[a[1]] = (int*)malloc(sizeof(int) * (wolf->cols));
//		a[2] = 0;
//		while (tab[a[2]])
//		{
//			wolf->map[a[1]][a[2]] = ft_atoi(tab[a[2]]);
//			free(tab[a[2]]);
//			a[2]++;
//		}
//		free(tab);
//		ft_strdel(&line);
//		a[1]++;
//	}
//	ft_strdel(&line);
//	close(wolf->fd);
//	return ((a[0] == -1) ? -1 : 0);
//
//}


int valid(t_rtv *rtv)
{
//	if ((valid1(rtv) != 0))
//	{
//		write(1, "one\n", 4);
//		return (-1);
//	}
//	else if ((valid2(rtv) != 0))
//	{
//		write(1, "two\n", 4);
//		return (-1);
//	}
//	render2(rtv);
//	if (valid_scene(rtv) != 0)
//	{
//		write(1, "three\n", 6);
//		return (-1);
//	}
//	//if (valid_scene2(rtv) != 0)
//	//{
//	//	write(1, "four\n", 5);
//	//	return (-1);
//	//}
//	//if (valid_objects(rtv) != 0)
//	//{
//		write(1, "five\n", 5);
//		return (-1);
//	}
	printf("%f\n", rtv->cam->pos.x);
	printf("%f\n", rtv->cam->pos.y);
	printf("%f\n", rtv->cam->pos.z);
	printf("%f\n", rtv->cam->dir.x);
	printf("%f\n", rtv->cam->dir.y);
	printf("%f\n", rtv->cam->dir.z);

	printf("%f\n", rtv->sphere->color.r);
	printf("%f\n", rtv->sphere->color.g);
	printf("%f\n", rtv->sphere->color.b);
	printf("%f\n", rtv->sphere->radius);

	printf("%f\n", rtv->light.pos.x);
	printf("%f\n", rtv->light.pos.y);
	printf("%f\n", rtv->light.pos.z);
	return (0);

}

*/


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
			if (((line[i] >= 48) && (line[i] <= 57)) || (line[i] == ' ') ||
				(line[i] == '\n') || (line[i] == '-') || (line[i] == '\t')
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

int count(t_rtv *rtv)
{
	char *line;
	int i;
	int j;

	j = 0;
	rtv->fd = open(rtv->name, O_RDONLY);
	while (get_next_line(rtv->fd, &line) > 0)
	{
		i = 0;
		while (line[i])
		{
			if (line[i] == '\n')
				j++;
		}
		ft_strdel(&line);
	}
	ft_strdel(&line);
	close(rtv->fd);
	return (j);
}

int ft_line_count(char *line)
{
	int i;

	i = 0;
	while ((line[i] != '\n') && (line[i] != '\0'))
		i++;
	return (i);
}

int valid_scene(t_rtv *rtv)
{
	int i;

	if (ft_strcmp(rtv->scene[0], "scene\0") != 0)
	{
		printf("%s\n", rtv->scene[0]);
		return (-1);
	}
	else if (ft_strcmp(rtv->scene[1], "{\0") != 0)
	{
		printf("%s\n", rtv->scene[1]);
		return (-1);
	}
	else if (ft_strcmp(rtv->scene[4], "}\0") != 0)
	{
		printf("%s\n", rtv->scene[4]);
		return (-1);
	}
	else if (ft_strcmp(rtv->scene[5], "content\0") != 0)
	{
		printf("%s\n", rtv->scene[5]);
		return (-1);
	}
	else if (ft_strcmp(rtv->scene[6], "{\0") != 0)
	{
		printf("%s\n", rtv->scene[6]);
		return (-1);
	}
	i = 0;
	while (rtv->scene[i] != NULL)
		i++;
	if (ft_strcmp(rtv->scene[i - 1], "}\0") != 0)
	{
		printf("%s\n", rtv->scene[i - 1]);
		return (-1);
	}
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

int valid_scene2(t_rtv *rtv)
{
	char *str;
	int i;

	rtv->cam = (t_cam *)malloc(sizeof(t_cam));
	//rtv->cam->pos = malloc(sizeof(t_vector3));
	//rtv->cam->dir = malloc(sizeof(t_vector3));
	if (ft_strncmp(rtv->scene[2], "	cam_pos(", 9) != 0)
		return (-1);
	str = rtv->scene[2];
	i = 0;
	while(i != 9)
	{
		str++;
		i++;
	}
	if (valid_count(str) != 0)
		return (-1);
	rtv->cam->pos.x = ft_atoi(str);
	while (*str != ' ')
		str++;
	str++;
	rtv->cam->pos.y = ft_atoi(str);
	while (*str != ' ')
		str++;
	rtv->cam->pos.z = ft_atoi(str);
	if (ft_strncmp(rtv->scene[3], "	cam_dir(", 9) != 0)
		return (-1);
	str = rtv->scene[3];
	i = 0;
	while(i != 9)
	{
		str++;
		i++;
	}
	if (valid_count(str) != 0)
		return (-1);
	rtv->cam->dir.x = ft_atoi(str);
	while (*str != ' ')
		str++;
	str++;
	rtv->cam->dir.y = ft_atoi(str);
	while (*str != ' ')
		str++;
	rtv->cam->dir.z = ft_atoi(str);
	return(0);
}

t_light *init_light(t_light *light)
{
	light = (t_light *)malloc(sizeof(t_light));
	//light->intensity = (t_color *)malloc(sizeof(t_vector3));
	//light->pos = (t_vector3 *)malloc(sizeof(t_vector3));
	return (light);
}

t_plane *init_plane(t_plane *plane)
{
	plane = (t_plane *)malloc(sizeof(t_plane));
	//plane->color = (t_color *)malloc(sizeof(t_vector3));
	//plane->pos = (t_vector3 *)malloc(sizeof(t_vector3));
	//plane->rot = (t_vector3 *)malloc(sizeof(t_vector3));
	return (plane);
}

t_sphere *init_sphere(t_sphere *sphere)
{
	sphere = (t_sphere *)malloc(sizeof(t_sphere));
	//sphere->color = (t_color *)malloc(sizeof(t_vector3));
	//sphere->center = (t_vector3 *)malloc(sizeof(t_vector3));
	return (sphere);
}

void add_light(t_light *light, t_rtv *rtv)
{
	t_light *begin;

	if (!rtv->light)
		rtv->light = light;
	else
	{
		begin = rtv->light;
		while (begin->next != NULL)
			begin = begin->next;
		begin->next = light;
	}
}

void add_plane(t_plane *plane, t_rtv *rtv)
{
	t_plane *begin;

	if (!rtv->plane)
		rtv->plane = plane;
	else
	{
		begin = rtv->plane;
		while (begin->next != NULL)
			begin = begin->next;
		begin->next = plane;
	}
}

void add_sphere(t_sphere *sphere, t_rtv *rtv)
{
	t_sphere *begin;

	if (!rtv->sphere)
		rtv->sphere = sphere;
	else
	{
		begin = rtv->sphere;
		while (begin->next != NULL)
			begin = begin->next;
		begin->next = sphere;
	}
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
	return (0);
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

int valid_objects(t_rtv *rtv)
{
	char *str;
	t_light *light;
	t_plane *plane;
	t_sphere *sphere;
	int i;
	int k;
	int j;

	i = 0;
	while (rtv->scene[i] != NULL)
		i++;
	k = i;
	i = 7;
	while (i != k - 1)
	{
		if (ft_strcmp(rtv->scene[i], "	object(light)\0") == 0)
		{
			if ((i + 4) >= k)
				return (-1);
			if (ft_strcmp(rtv->scene[i + 1], "	{\0") != 0 || ft_strcmp(rtv->scene[i + 4], "	}\0") != 0)
				return (-1);
			if (ft_strncmp(rtv->scene[i + 2], "		col(", 6) != 0)
				return (-1);
			if (ft_strncmp(rtv->scene[i + 3], "		pos(", 6) != 0)
				return (-1);
			light = init_light(light);
			str = rtv->scene[i + 2];
			if (data_color(str, &light->intensity, 6) != 0)
				return (-1);
			str = rtv->scene[i + 3];
			if (data_vector(str, &light->pos, 6) != 0)
				return (-1);
			add_light(light, rtv);
			i = i + 5;
		}
		else if (ft_strcmp(rtv->scene[i], "	object(plane)\0") == 0)
		{
			if ((i + 5) >= k)
				return (-1);
			if (ft_strcmp(rtv->scene[i + 1], "	{\0") != 0 || ft_strcmp(rtv->scene[i + 5], "	}\0") != 0)
				return (-1);
			if (ft_strncmp(rtv->scene[i + 2], "		col(", 6) != 0)
				return (-1);
			if (ft_strncmp(rtv->scene[i + 3], "		pos(", 6) != 0)
				return (-1);
			if (ft_strncmp(rtv->scene[i + 4], "		rot(", 6) != 0)
				return (-1);
			plane = init_plane(plane);
			str = rtv->scene[i + 2];
			if (data_color(str, &plane->color, 6) != 0)
				return (-1);
			str = rtv->scene[i + 3];
			if (data_vector(str, &plane->pos, 6) != 0)
				return (-1);
			str = rtv->scene[i + 4];
			if (data_vector(str, &plane->rot, 6) != 0)
				return (-1);
			add_plane(plane, rtv);
			i = i + 6;
		}
		else if (ft_strcmp(rtv->scene[i], "	object(sphere)\0") == 0)
		{
			if ((i + 5) >= k)
				return (-1);
			if (ft_strcmp(rtv->scene[i + 1], "	{\0") != 0 || ft_strcmp(rtv->scene[i + 5], "	}\0") != 0)
				return (-1);
			if (ft_strncmp(rtv->scene[i + 2], "		col(", 6) != 0)
				return (-1);
			if (ft_strncmp(rtv->scene[i + 3], "		pos(", 6) != 0)
				return (-1);
			if (ft_strncmp(rtv->scene[i + 4], "		size(", 7) != 0)
				return (-1);
			sphere = init_sphere(sphere);
			str = rtv->scene[i + 2];
			if (data_color(str, &sphere->color, 6) != 0)
				return (-1);
			str = rtv->scene[i + 3];
			if (data_vector(str, &sphere->center, 6) != 0)
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
			sphere->radius = ft_atoi(str);
			add_sphere(sphere, rtv);
			i = i + 6;
		}
	}
	return (0);
}

void render2(t_rtv *rtv)
{
	char *line;

	rtv->buf = ft_strnew(1);
	rtv->fd = open(rtv->name, O_RDONLY);
	while (get_next_line(rtv->fd, &line) > 0)
		rtv->buf = ft_strjoin(rtv->buf, (ft_strjoin(line, "\n")));
	rtv->scene = ft_strsplit(rtv->buf, '\n');
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
	if (valid_scene(rtv) != 0) // if no content or scene?
	{
		write(1, "three\n", 6);
		return (-1);
	}
	if (valid_scene2(rtv) != 0)  // norm, but if '/t' or '+' or something else, it will be not a valid
	{
		write(1, "four\n", 5);
		return (-1);
	}
	if (valid_objects(rtv) != 0) // norm
	{
		write(1, "five\n", 5);
		return (-1);
	}
	/*while (rtv->sphere)
	{
		printf("%f\n", rtv->sphere->center.x);
		printf("%f\n", rtv->sphere->center.y);
		printf("%f\n", rtv->sphere->center.z);
		printf("%f\n", rtv->sphere->radius);
		rtv->sphere = rtv->sphere->next;
	}
	printf("%f\n", rtv->sphere->center.x);
	printf("%f\n", rtv->sphere->center.y);
	printf("%f\n", rtv->sphere->center.z);
	*/
	printf("%f\n", rtv->sphere->color.r);
	printf("%f\n", rtv->sphere->color.g);
	printf("%f\n", rtv->sphere->color.b);
	//printf("%f\n", rtv->sphere->radius);
	return (0);

}


static	int		close_app(t_rtv *rtv)
{
	free(rtv);
	exit(0);
}

static	void	ft_error(char *msg, int i)
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
		rtv->image.ptr[(WIDTH * y + x) * rtv->image.bpp] = (char) color.r;
		rtv->image.ptr[(WIDTH * y + x) * rtv->image.bpp + 1] = (char) color.g;
		rtv->image.ptr[(WIDTH * y + x) * rtv->image.bpp + 2] = (char) color.b;

	}
}

/*void init_shapes(t_rtv *rtv)
{
	rtv->cam = malloc(sizeof(t_cam));
	//rtv->sphere = malloc(sizeof(t_sphere));
	//rtv->light = malloc(sizeof(t_light));
	t_vector3 center = new_vector3(0, 0, 20);
	t_color	color = set_color(100, 100, 100);
	rtv->sphere = new_sphere(center, 5, color);

	//center = new_vector3(10, 10, 10);
	//color = set_color(255, 0, 0);
	//rtv->sphere.next = new_sphere(center, 10., color);

	rtv->cam->pos = new_vector3(0, 0, 0);
	rtv->cam->dir = new_vector3(0, 0, 1);
	rtv->light = malloc(sizeof(t_light));
	rtv->light->pos = new_vector3(-50, 50, -100);
	rtv->light->intensity = set_color(0, 255, 255);
}
*/
void *draw_scene(void *rtv)
{
	t_threads	thread;
	pthread_t		id;
	int 		x;
	int			y;
	t_color		color;

	thread.start = 0;
	id = pthread_self();
	while (id != ((t_rtv*)rtv)->threads[thread.start])
		thread.start++;
	thread.end = THREAD_WIDTH * (thread.start + 1);
	thread.start = THREAD_WIDTH * thread.start;
	y = HEIGHT;
	while (y > -1)
	{
		x = thread.start;
		while (x < thread.end)
		{
			color = calculate_color((t_rtv*)rtv, x , y);
			img_pixel_put_one((t_rtv*)rtv, x , y, color);
			x++;
		}
		y--;
	}
	pthread_exit(NULL);
}

int rtv_pthread(t_rtv *rtv)
{
	int i;
	//int 		x;
	//int			y;
	//int Sx;
	//int Sy;
	//int Cw;
	//int Ch;
	//t_color		color;
	
	i = -1;
	while (++i < THREAD_NUM)
		pthread_create(&rtv->threads[i], NULL, draw_scene, rtv);
	while (i--)
		pthread_join(rtv->threads[i], NULL);
	
	/*y = 0;  // если использовать этот цикл, то рисует немного по другому, чем через многопоточность
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			color = calculate_color((t_rtv*)rtv, x , y);
			img_pixel_put_one((t_rtv*)rtv, x , y, color);
			x++;
		}
		y++;
	}
	*/
	/*Cw = WIDTH / 2;
	Ch = HEIGHT / 2;

	x = -Cw;  
	while (x <= Cw)
	{
		y = -Ch;
		while (y <= Ch)
		{
			color = calculate_color((t_rtv*)rtv, x , y);
			Sx = Cw + x;
			Sy = Ch - y;
			img_pixel_put_one((t_rtv*)rtv, Sx , Sy, color);
			y++;
		}
		x++;
	
	}
	*/mlx_put_image_to_window(rtv->mlx, rtv->window, rtv->image.image, 0, 0);
	return (0);
}

int				main(int argc, char **argv)
{
	t_rtv *rtv;

	if (argc > 2)
		ft_error("too many parameters\n", 0);
	else if (argc == 1)
		ft_error("use scene from scenes\n", 0);
	if (!(rtv = (t_rtv *)malloc(sizeof(t_rtv))))
		ft_error("can't allocate enough memory for the structure\n", 0);
	rtv->name = argv[1];
	//init_shapes(rtv);
	if (valid(rtv) != 0)
	{
		free(rtv);
		ft_error("something is wrong with scene input\n", 0);
	}
	init(rtv);
	mlx_expose_hook(rtv->window, rtv_pthread, rtv);
	mlx_hook(rtv->window, 3, 1L << 1, key_release, rtv);
	mlx_hook(rtv->window, 17, 1L << 17, close_app, rtv);
	mlx_loop(rtv->mlx);
	return (0);
}
