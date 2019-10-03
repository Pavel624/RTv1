/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsatterf <rsatterf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 13:32:35 by rsatterf          #+#    #+#             */
/*   Updated: 2019/10/02 18:35:12 by rsatterf         ###   ########.fr       */
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

	rtv->cam.pos = (t_vector3*)malloc(sizeof(t_vector3));
	rtv->cam.dir = (t_vector3*)malloc(sizeof(t_vector3));
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
	rtv->cam.pos->x = ft_atoi(str);
	while (*str != ' ')
		str++;
	str++;
	rtv->cam.pos->y = ft_atoi(str);
	while (*str != ' ')
		str++;
	rtv->cam.pos->z = ft_atoi(str);
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
	rtv->cam.dir->x = ft_atoi(str);
	while (*str != ' ')
		str++;
	str++;
	rtv->cam.dir->y = ft_atoi(str);
	while (*str != ' ')
		str++;
	rtv->cam.dir->z = ft_atoi(str);
	return(0);
}

void init_light(t_rtv *rtv)
{
	rtv->light = (t_light *)malloc(sizeof(t_light));
	rtv->light->color = (t_vector3*)malloc(sizeof(t_vector3));
	rtv->light->pos = (t_vector3*)malloc(sizeof(t_vector3));
}

void init_plane(t_rtv *rtv)
{
	rtv->plane = (t_plane *)malloc(sizeof(t_plane));
	rtv->plane->color = (t_vector3*)malloc(sizeof(t_vector3));
	rtv->plane->pos = (t_vector3*)malloc(sizeof(t_vector3));
	rtv->plane->rot = (t_vector3*)malloc(sizeof(t_vector3));
}

void init_sphere(t_rtv *rtv)
{
	rtv->sphere = (t_sphere *)malloc(sizeof(t_sphere));
	rtv->sphere->color = (t_vector3*)malloc(sizeof(t_vector3));
	rtv->sphere->center = (t_vector3*)malloc(sizeof(t_vector3));
}

int	data(char *str, t_vector3 *vec, int k)
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
			init_light(rtv);
			if (ft_strncmp(rtv->scene[i + 2], "		col(", 6) != 0)
				return (-1);
			str = rtv->scene[i + 2];
			if (data(str, rtv->light->color, 6) != 0)
				return (-1);
			if (ft_strncmp(rtv->scene[i + 3], "		pos(", 6) != 0)
				return (-1);
			str = rtv->scene[i + 3];
			if (data(str, rtv->light->pos, 6) != 0)
				return (-1);
			i = i + 5;
		}
		else if (ft_strcmp(rtv->scene[i], "	object(plane)\0") == 0)
		{
			//if ((i + 4) >= k)
				//return (-1);
			if (ft_strcmp(rtv->scene[i + 1], "	{\0") != 0 || ft_strcmp(rtv->scene[i + 5], "	}\0") != 0)
				return (-1);
			init_plane(rtv);
			if (ft_strncmp(rtv->scene[i + 2], "		col(", 6) != 0)
				return (-1);
			str = rtv->scene[i + 2];
			if (data(str, rtv->plane->color, 6) != 0)
				return (-1);
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
			init_sphere(rtv);
			if (ft_strncmp(rtv->scene[i + 2], "		col(", 6) != 0)
				return (-1);
			str = rtv->scene[i + 2];
			if (data(str, rtv->sphere->color, 6) != 0)
				return (-1);
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

/*int render1(t_rtv *rtv)
{
	int		a[3];
	char	*line;
	char	**tab;

	rtv->scene = (char **)malloc(sizeof(char *) * ());
	a[1] = 0;
	wolf->fd = open(wolf->name, O_RDONLY);
	while ((a[0] = get_next_line(wolf->fd, &line)) > 0)
	{
		tab = ft_strsplit(line, ' ');
		wolf->map[a[1]] = (int*)malloc(sizeof(int) * (wolf->cols));
		a[2] = 0;
		while (tab[a[2]])
		{
			wolf->map[a[1]][a[2]] = ft_atoi(tab[a[2]]);
			free(tab[a[2]]);
			a[2]++;
		}
		free(tab);
		ft_strdel(&line);
		a[1]++;
	}
	ft_strdel(&line);
	close(wolf->fd);
	return ((a[0] == -1) ? -1 : 0);

}
*/

int valid(t_rtv *rtv)
{
	if ((valid1(rtv) != 0))
	{
		write(1, "one\n", 4);
		return (-1);
	}
	else if ((valid2(rtv) != 0))
	{
		write(1, "two\n", 4);
		return (-1);
	}
	render2(rtv);
	if (valid_scene(rtv) != 0)
	{
		write(1, "three\n", 6);
		return (-1);
	}
	if (valid_scene2(rtv) != 0)
	{
		write(1, "four\n", 5);
		return (-1);
	}
	if (valid_objects(rtv) != 0)
	{
		write(1, "five\n", 5);
		return (-1);
	}
	/*printf("%f\n", rtv->cam.pos->x);
	printf("%f\n", rtv->cam.pos->y);
	printf("%f\n", rtv->cam.pos->z);
	printf("%f\n", rtv->cam.dir->x);
	printf("%f\n", rtv->cam.dir->y);
	printf("%f\n", rtv->cam.dir->z);
	*/
	printf("%f\n", rtv->sphere->color->x);
	printf("%f\n", rtv->sphere->color->y);
	printf("%f\n", rtv->sphere->color->z);
	printf("%f\n", rtv->sphere->radius);
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

void	img_pixel_put_one(t_image *img, int x, int y, int color)
{
	if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
		*(int *)(img->ptr + (int)((WIDTH * y + x) * img->bpp)) = color;
}

void normalize(t_vector3 *vec)
{
	double len;

	len = sqrt(pow(vec->x, 2) + pow(vec->y, 2) + pow(vec->z, 2));
	vec->x /= len;
	vec->y /= len;
	vec->z /= len;
}

double ray_intersect(t_cam *ray, t_sphere *sphere)
{
	t_vector3 *len;
	double t0, t1;

	len = sub_vector3(sphere->center, ray->pos, 0);
	double tca = scalar_vector3(len,ray->dir, 0);
	double d2 = scalar_vector3(len, len, 0) - tca * tca;

	if (d2 > sphere->radius * sphere->radius)
		return (0);
	float thc = sqrtf(sphere->radius * sphere->radius - d2);
	t0 = tca - thc;
	t1 = tca + thc;
	if (t0 < 0 && t1 < 0)
		return (0);
	if (t0 < t1)
		return (t0);
	else
		return (t1);

}

t_vector3 *get_normal(t_vector3 *vec, t_sphere *sphere)
{
	t_vector3 *vector3;

	vector3 = mult_nbr_vector3(sub_vector3(vec, sphere->center, 0), -1 / sphere->radius, 0);
	return (vector3);
}

static int loop()
{
	return (1);
}

int				main(int argc, char **argv)
{
	t_rtv *rtv;

	if (argc > 2)
		ft_error("too many parameters\n", 0);
	else if (argc == 1)
		ft_error("use scene from scenes\n", 0);
	if (!(rtv = (t_rtv *)malloc(sizeof(t_rtv))))
		ft_error("Can't allocate enough memory for the structure\n", 0);
	rtv->name = argv[1];
	

	if (valid(rtv) != 0)
	{
		free(rtv);
		ft_error("error scene\n", 0);
	}
	init(rtv);

	t_cam *camera;
	t_sphere *sphere;
	t_sphere *sphere1;
	t_light	*light;

	camera = malloc(sizeof(t_cam));			//add malloc protection
	sphere = malloc(sizeof(t_sphere));
	sphere1 = malloc(sizeof(t_sphere));
	light = malloc(sizeof(t_light));

	sphere->center = new_vector3(3, 10, -16);
	sphere->radius = 5.0;

	sphere1->center = new_vector3(0, 0, -16);
	sphere1->radius = 5.0;

	camera->pos = new_vector3(0, 0, 0);

	light->pos = new_vector3(0, 0, 0);

	int i, j = 0;

	double fov = M_PI / 2.;

	while (j < HEIGHT)
	{
		i = 0;
		while (i < WIDTH)
		{
			double x =  (2 * (i + 0.5) / (double) WIDTH  - 1) * tan(fov/2.) * WIDTH / (double) HEIGHT;
			double y = -(2 * (j + 0.5) / (double) HEIGHT - 1) * tan(fov/2.);

			camera->dir = new_vector3(x, y, -1);
			normalize(camera->dir);

			if (ray_intersect(camera, sphere) > 0.0)
				img_pixel_put_one(&rtv->image, i, j, 0xFFFFFF);
			//else
				//img_pixel_put_one(&rtv->image, i, j, 0xFF00FF);

			if (ray_intersect(camera, sphere1) > 0.0)
				img_pixel_put_one(&rtv->image, i, j, 0xFF0000);
			i++;
		}
		j++;
	}
	mlx_put_image_to_window(rtv->mlx, rtv->window, rtv->image.image, 0, 0);
	mlx_hook(rtv->window, 3, 1L << 1, key_release, rtv);
	mlx_hook(rtv->window, 17, 1L << 17, close_app, rtv);
	mlx_loop_hook(rtv->mlx, loop, rtv);
	mlx_loop(rtv->mlx);
	return (0);
}
