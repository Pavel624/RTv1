/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsatterf <rsatterf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 13:24:18 by rsatterf          #+#    #+#             */
/*   Updated: 2019/09/24 20:01:45 by rsatterf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_H
# define RTV1_H

# include "../libft/libft.h"
# ifdef __APPLE__
#  include <mlx.h>
#  define OS_VER 0
#  define KEY_ESC 53
# elif __linux__
#  define OS_VER 1
#  include "../minilibx/mlx.h"
#  define KEY_ESC 65307
# endif

# include <stdlib.h>
# include <fcntl.h>
# include <sys/types.h>

# define WIDTH 1024
# define HEIGHT 768

typedef struct	s_image
{
	void		*image;
	char		*ptr;
	int			bpp;
	int			line_s;
	int			endian;
}				t_image;

typedef struct	s_vec
{
	double		x;
	double		y;
	double		z;
}				t_vec;

typedef struct	s_sphere
{
	t_vec		centr;
	double		radius;
}				t_sphere;

typedef struct	s_cam
{
	t_vec		pos;
	t_vec		dir;
}				t_cam;


typedef struct	s_rtv
{
	void		*mlx;
	void		*window;
	t_image		image;
	char		*name;
	int			fd;
	char		**scene;
	char		*buf;

}				t_rtv;

#endif