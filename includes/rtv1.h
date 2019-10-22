/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsatterf <rsatterf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 13:24:18 by rsatterf          #+#    #+#             */
/*   Updated: 2019/10/02 17:22:10 by rsatterf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_H
# define RTV1_H

# include "../libft/libft.h"
# include "vector3.h"
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
# include <math.h>
# include <pthread.h>

# define WIDTH 1024
# define HEIGHT 768
# define THREAD_NUM 4
# define THREAD_WIDTH (WIDTH / THREAD_NUM)
# define ASPECT_RATIO (WIDTH / HEIGHT)
# define FOV 1.0

typedef struct	s_image
{
	void		*image;
	char		*ptr;
	int			bpp;
	int			line_s;
	int			endian;
}				t_image;

typedef struct	s_threads
{
	int			start;
	int			end;
}				t_threads;

typedef struct	s_color
{
    double      r;
    double      g;
    double      b;
}				t_color;

typedef struct	s_cam
{
    t_vector3	pos;
    t_vector3	dir;
}				t_cam;

typedef struct	s_ray
{
    t_vector3	origin;
    t_vector3	dir;
}				t_ray;

typedef struct	s_light
{
    t_vector3	pos;
    t_color     intensity;
    struct s_light *next;
}				t_light;

typedef struct s_cur_ray
{
	t_ray		ray;
	t_color		color;
	t_vector3	norm;
	double		k;
}				t_cur_ray;

typedef struct	s_sphere
{
	t_color	color;
	t_vector3	center;
	double		radius;
	struct s_sphere *next;
}				t_sphere;

typedef struct	s_plane
{
	t_color     color;
	t_vector3	pos;
	t_vector3	rot;
	struct s_plane *next;
}				t_plane;

typedef struct	s_cylinder
{
    t_color	    color;
    t_vector3	center;
    t_vector3   dir;
    double      radius;
    struct s_cylinder *next;
}				t_cylinder;

typedef struct	s_rtv
{
	void		*mlx;
	void		*window;
	t_image		image;
	t_cam		*cam;
	t_light		light;
	t_plane		*plane;
	t_sphere	sphere;
	t_cylinder  *cylinder;
	pthread_t	threads[THREAD_NUM];
	char		*name;
	int			fd;
	char		**scene;
	char		*buf;

}				t_rtv;

t_sphere 	new_sphere(t_vector3 center, double radius, t_color color);
int     	intersect_sphere(t_sphere sphere, t_ray ray, double *point);
int     	calc_intersect(double k1, double k2, double k3, double *point);

t_color 	set_color(double r, double g, double b);
t_color		calculate_color(t_rtv *rtv, int x, int y);
t_vector3 	calculate_ray_dir(int x, int y, t_rtv *rtv);
void		calculate_ray(t_rtv *rtv, t_cur_ray *cur_ray);
void 		get_light(t_rtv *rtv, t_cur_ray *cur_ray);
double 		light_shape(t_ray light_ray, t_vector3 norm, double k);

int 		key_release(int key, t_rtv *rtv);

void		img_pixel_put_one(t_rtv *rtv, int x, int y, t_color color);

#endif