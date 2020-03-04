/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsatterf <rsatterf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 13:32:35 by rsatterf          #+#    #+#             */
/*   Updated: 2020/03/03 13:02:05 by rsatterf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

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

void			img_pixel_put_one(t_rtv *rtv, int x, int y, t_color color)
{
	if (x > 0 && x < WIDTH && y > 0 && y < HEIGHT)
	{
		rtv->image.ptr[(WIDTH * y + x) * rtv->image.bpp + 2] =
		(char)fmin(color.r * 255.0f, 255.0f);
		rtv->image.ptr[(WIDTH * y + x) * rtv->image.bpp + 1] =
		(char)fmin(color.g * 255.0f, 255.0f);
		rtv->image.ptr[(WIDTH * y + x) * rtv->image.bpp] =
		(char)fmin(color.b * 255.0f, 255.0f);
	}
}

void			find_basis(t_cam *cam)
{
	t_vector3 tmp;

	if (cam->dir.x == 0 && fabs(cam->dir.y) == 1 && cam->dir.z == 0)
		tmp = new_vector3(0, 0, -cam->dir.y);
	else
		tmp = new_vector3(0, 1, 0);
	cam->i = cross_vector3(tmp, cam->dir);
	cam->i = normalize(cam->i);
	cam->j = cross_vector3(cam->dir, cam->i);
	cam->j = normalize(cam->j);
}

int				draw(t_rtv *rtv)
{
	int			x;
	int			y;
	t_color		color;

	x = 0;
	find_basis(rtv->cam);
	while (x < WIDTH)
	{
		y = 0;
		while (y < HEIGHT)
		{
			color = calculate_color((t_rtv*)rtv, x, y);
			img_pixel_put_one((t_rtv*)rtv, x, y, color);
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
		ft_error(TOO_MANY_PARAMS);
	else if (argc == 1)
		ft_error(USE_SCENE);
	if (!(rtv = (t_rtv *)malloc(sizeof(t_rtv))))
		ft_error(RTV_ERR);
	rtv->name = argv[1];
	valid(rtv);
	init(rtv);
	mlx_expose_hook(rtv->window, draw, rtv);
	mlx_hook(rtv->window, 3, 1L << 1, key_release, rtv);
	mlx_hook(rtv->window, 17, 1L << 17, close_app, rtv);
	mlx_loop(rtv->mlx);
	return (0);
}
