/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsatterf <rsatterf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 13:32:35 by rsatterf          #+#    #+#             */
/*   Updated: 2019/09/24 17:34:40 by rsatterf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

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
	init(rtv);
	mlx_hook(rtv->window, 17, 1L << 17, close_app, rtv);
	//mlx_loop_hook(rtv->mlx, loop, rtv);
	mlx_loop(rtv->mlx);
	return (0);
}
