/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsatterf <rsatterf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 13:24:18 by rsatterf          #+#    #+#             */
/*   Updated: 2019/10/23 14:56:14 by rsatterf         ###   ########.fr       */
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

# define WIDTH 1080
# define HEIGHT 720
# define THREAD_NUM 4
# define THREAD_WIDTH (WIDTH / THREAD_NUM)
# define ASPECT_RATIO ((double) WIDTH / HEIGHT)

# define CAM 0
# define LIGHT 1
# define SPHERE 2
# define PLANE 3
# define CYLINDER 4
# define CONE 5

#define AMBIENT 0.15

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

typedef struct	s_ray
{
    t_vector3	origin;
    t_vector3	dir;
}				t_ray;

typedef struct s_cur_ray
{
	t_ray		ray;
	t_color		color;
	t_vector3	norm;
	double		k;
}				t_cur_ray;

typedef struct s_prop
{
	t_color		color;
	double			diffuse;
	int 		specular;
}				t_prop;

typedef struct	s_light
{
	t_vector3	pos;
	t_color		color;
	int 		brightness;
}				t_light;

typedef struct	s_cam
{
	t_vector3	pos;
	t_vector3	dir;
	int			fov;
}				t_cam;

typedef struct	s_sphere
{
	t_prop		prop;
	t_vector3	center;
	int			radius;
}				t_sphere;

typedef struct	s_plane
{
	t_prop		prop;
	t_vector3	norm;
	int			point;
}				t_plane;

typedef struct	s_cylinder
{
	t_prop		prop;
    t_vector3	center;
    t_vector3   dir;
    int     	 radius;
}				t_cylinder;

typedef struct	s_cone
{
	t_prop		prop;
	t_vector3	center;
	t_vector3   dir;
	double 	    angle;
}				t_cone;

typedef struct	s_rtv
{
	void		*mlx;
	void		*window;
	t_image		image;
	t_cam		*cam;
	t_light		*light;
	t_plane		*plane;
	t_sphere	*sphere;
	t_cylinder  *cylinder;
	t_cone      *cone;
	int 		nbr[6];
	pthread_t	threads[THREAD_NUM];
	char		*name;
	int			fd;
	char		**scene;
	char		*buf;

}				t_rtv;

/* 		----------------
** 		|parse_shapes.c|
**		----------------
*/

void		parse_plane(t_rtv *rtv, char **words, int *index);
void		parse_sphere(t_rtv *rtv, char **words, int *index);
void		parse_cylinder(t_rtv *rtv, char **words, int *index);
void		parse_cone(t_rtv *rtv, char **words, int *index);

int			check_color(t_color color);

int			validation (t_rtv *rtv);

void		ft_error(char *msg, int i);

t_sphere 	new_sphere(t_vector3 center, double radius);
t_plane 	new_plane(t_vector3 norm, double point);
t_cylinder  new_cylinder(t_vector3 dir, t_vector3 center, double radius);
t_cone      new_cone(t_vector3 dir, t_vector3 center, double angle);

int     	intersect_sphere(t_sphere sphere, t_ray *ray, double *hit);
int 		intersect_plane(t_plane plane, t_ray *ray, double *hit);
int 		intersect_cylinder(t_cylinder cylinder, t_ray *ray, double *hit);
int			intersect_cone(t_cone cone, t_ray *ray, double *hit);

int     	calc_intersect(double k1, double k2, double k3, double *hit);
t_color 	set_color(double r, double g, double b);
t_color		calculate_color(t_rtv *rtv, int x, int y);
t_vector3 	calculate_ray_dir(int x, int y, t_rtv *rtv);
int			calculate_ray(t_rtv *rtv, t_cur_ray *cur_ray);

void 		get_light(t_rtv *rtv,t_vector3 hit_vector, t_cur_ray *cur_ray, t_prop prop);
double 		diffuse(t_ray light_ray, t_vector3 norm);
void 		color_diffuse(t_color *color, double f, t_light light, t_prop prop, double len);
double 		specular(t_ray light_ray, t_vector3 norm, t_ray *ray, t_prop prop);
t_prop 		find_prop(t_rtv *rtv, int item, int *current);

int 		is_in_shadow(t_ray *light_ray, t_rtv *rtv, double t);
void		reflect_ray(t_ray *ray, t_vector3 norm, t_vector3 hit_vector);

int 		key_release(int key, t_rtv *rtv);

void		img_pixel_put_one(t_rtv *rtv, int x, int y, t_color color);

t_vector3 	find_norm(t_rtv *rtv, int item, int *current, t_vector3 hit_point, t_ray ray);

int 		find_closest_plane(t_ray ray, t_rtv *rtv, double *t);
int 		find_closest_sphere(t_ray ray, t_rtv *rtv, double *t);
int 		find_closest_cylinder(t_ray ray, t_rtv *rtv, double *t);
int			find_closest_cone(t_ray ray, t_rtv *rtv, double *t);
int 		find_closest_object(t_ray ray, t_rtv *rtv, t_vector3 *hit_vector, int *current);

t_vector3   find_norm_cylinder(t_vector3 hit_point, t_vector3 center, t_vector3 dir);
t_vector3	find_norm_cone(t_vector3 hit_point, t_vector3 center, t_vector3 dir, double angle);

#endif