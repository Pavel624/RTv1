/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsatterf <rsatterf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 13:32:35 by rsatterf          #+#    #+#             */
/*   Updated: 2019/09/24 20:31:22 by rsatterf         ###   ########.fr       */
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
	else if (ft_strcmp(rtv->scene[7], "	object(light)\0") != 0)
	{
		printf("%s\n", rtv->scene[7]);
		return (-1);
	}
	else if (ft_strcmp(rtv->scene[8], "	{\0") != 0)
	{
		printf("%s\n", rtv->scene[8]);
		return (-1);
	}
	else if (ft_strcmp(rtv->scene[11], "	}\0") != 0)
	{
		printf("%s\n", rtv->scene[11]);
		return (-1);
	}
	else if (ft_strcmp(rtv->scene[12], "	object(plane)\0") != 0)
	{
		printf("%s\n", rtv->scene[12]);
		return (-1);
	}
	else if (ft_strcmp(rtv->scene[13], "	{\0") != 0)
	{
		printf("%s\n", rtv->scene[13]);
		return (-1);
	}
	else if (ft_strcmp(rtv->scene[17], "	}\0") != 0)
	{
		printf("%s\n", rtv->scene[17]);
		return (-1);
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
	char *str;

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
	str = rtv->scene[2];
	printf("%s\n", str);
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

void normalize(t_vector3 *vec)
{
	double len;

	len = sqrt(pow(vec->x, 2) + pow(vec->y, 2) + pow(vec->z, 2));
	vec->x /= len;
	vec->y /= len;
	vec->z /= len;
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

	camera = malloc(sizeof(t_cam));			//add malloc protection
	sphere = malloc(sizeof(t_sphere));

	sphere->center = *new_vector3(2,3,4);
	sphere->radius = 5.0;

	camera->pos = *new_vector3(0, 0, 0);

	int i = 0, j;

	double fov = M_PI / 3.;

	while (i < HEIGHT)
	{
		j = 0;
		while (j < WIDTH)
		{
			double x =  (2*(i + 0.5)/(double)WIDTH  - 1)*tan(fov/2.)*WIDTH/(double)HEIGHT;
			double y = -(2*(j + 0.5)/(double)HEIGHT - 1)*tan(fov/2.);

			camera->dir = *new_vector3(x, y, -1);
			normalize(&camera->dir);

			j++;
		}
		i++;
	}
	mlx_put_image_to_window(rtv->mlx, rtv->window, rtv->image.image, 0, 0);
	mlx_hook(rtv->window, 3, 1L << 1, key_release, rtv);
	mlx_hook(rtv->window, 17, 1L << 17, close_app, rtv);
	mlx_loop_hook(rtv->mlx, loop, rtv);
	mlx_loop(rtv->mlx);
	return (0);
}
