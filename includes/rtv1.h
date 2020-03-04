/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsatterf <rsatterf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 13:24:18 by rsatterf          #+#    #+#             */
/*   Updated: 2020/03/03 13:46:34 by rsatterf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_H
# define RTV1_H

# include "libft.h"
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
# include <math.h>

# define WIDTH 1080
# define HEIGHT 720
# define ASPECT_RATIO ((double) WIDTH / HEIGHT)

# define CAM 0
# define LIGHT 1
# define SPHERE 2
# define PLANE 3
# define CYLINDER 4
# define CONE 5

# define T_RAY_MIN 0.001f
# define SPECULAR_COEF 1
# define BRIGHTNESS 1000
# define AMBIENT 0.015

enum {
	TOO_MANY_PARAMS = 1,
	USE_SCENE,
	RTV_ERR,
	MEM_ALLOC_ERR,
	OPEN_FILE_ERR,
	INVALID_SYMBOLS,
	CAM_OR_LIGHT_ERR,
	INVALID_OBJ
};

typedef struct	s_image
{
	void		*image;
	char		*ptr;
	int			bpp;
	int			line_s;
	int			endian;
}				t_image;

typedef struct	s_color
{
	double		r;
	double		g;
	double		b;
}				t_color;

typedef struct	s_ray
{
	t_vector3	origin;
	t_vector3	dir;
}				t_ray;

typedef struct	s_cur_ray
{
	t_ray		ray;
	t_color		color;
	t_vector3	norm;
	double		k;
}				t_cur_ray;

typedef struct	s_prop
{
	t_color		color;
	int			specular;
	int			reflection;
}				t_prop;

typedef struct	s_light
{
	t_vector3	pos;
	t_color		color;
	int			brightness;
}				t_light;

typedef struct	s_cam
{
	t_vector3	pos;
	t_vector3	dir;
	int			fov;
	t_vector3	i;
	t_vector3	j;
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
	t_vector3	dir;
	int			radius;
}				t_cylinder;

typedef struct	s_cone
{
	t_prop		prop;
	t_vector3	center;
	t_vector3	dir;
	double		angle;
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
	t_cylinder	*cylinder;
	t_cone		*cone;
	int			nbr[6];
	int			index[6];
	char		*name;
	int			i;
	int			j;
	int			k;
	int			l;
	int			e;
	int			fd;
	char		**scene;
	char		*buf;
}				t_rtv;

void			ft_error(int i);
int				intersect_sphere(t_sphere sphere, t_ray *ray, double *hit);
int				intersect_plane(t_plane plane, t_ray *ray, double *hit);
int				intersect_cylinder(t_cylinder cylinder,
				t_ray *ray, double *hit);
int				intersect_cone(t_cone cone, t_ray *ray, double *hit);
void			img_pixel_put_one(t_rtv *rtv, int x, int y, t_color color);
int				key_release(int key, t_rtv *rtv);
t_prop			find_prop(t_rtv *rtv, int item, int *cur);
t_vector3		find_norm_plane(t_rtv *rtv, int *current, t_ray ray);
t_vector3		find_norm_not_plane(t_rtv *rtv,
				int item, int *current, t_vector3 hit_point);
int				find_closest_object(t_ray ray, t_rtv *rtv,
				t_vector3 *hit_vector, int *cur_item);
int				calc_intersect(double k1, double k2, double k3, double *hit);
void			get_light(t_rtv *rtv, t_vector3 hit_point,
				t_cur_ray *cur_ray, t_prop prop);
t_vector3		calculate_ray_dir(int x, int y, t_rtv *rtv);
int				calculate_ray(t_rtv *rtv, t_cur_ray *cur_ray);
void			reflect_ray(t_ray *ray, t_vector3 norm, t_vector3 hit_vector);
t_color			set_color(double r, double g, double b);
void			color_diffuse(t_color *color, double k_mult_bright,
				t_light light, t_prop prop);
void			color_specular(t_color *color, double k,
				t_light light, double brightness);
t_color			calculate_color(t_rtv *rtv, int x, int y);
int				find_closest_plane(t_ray ray, t_rtv *rtv, double *t);
int				find_closest_sphere(t_ray ray, t_rtv *rtv, double *t);
int				find_closest_cylinder(t_ray ray, t_rtv *rtv, double *t);
int				find_closest_cone(t_ray ray, t_rtv *rtv, double *t);
t_vector3		find_norm_cylinder(t_vector3 hit_point,
				t_vector3 center, t_vector3 dir);
t_vector3		find_norm_cone(t_vector3 hit_point, t_vector3 center,
				t_vector3 dir, double angle);
int				valid_camera(t_rtv *rtv, int i, int k);
int				valid_light(t_rtv *rtv, int i, int k);
int				valid_plane(t_rtv *rtv, int i, int k);
int				valid_sphere(t_rtv *rtv, int i, int k);
int				valid_cylinder(t_rtv *rtv, int i, int k);
int				valid_cone(t_rtv *rtv, int i, int k);
char			*shift_str(char *str, int k);
int				help_valid_plane(t_rtv *rtv, int i, int k);
int				help_valid_sphere(t_rtv *rtv, int i, int k);
int				help_valid_sphere2(t_rtv *rtv, int i);
int				help_valid_cylinder(t_rtv *rtv, int i, int k);
int				help_valid_cylinder2(t_rtv *rtv, int i);
int				help_valid_cone(t_rtv *rtv, int i, int k);
int				help_valid_cone2(t_rtv *rtv, int i);
int				help_valid_cone3(t_rtv *rtv);
int				valid1(t_rtv *rtv);
int				help_valid2(char k, t_rtv *rtv);
int				valid2(t_rtv *rtv);
int				init_k(t_rtv *rtv);
int				valid_objects(t_rtv *rtv);
int				valid_count(char *str, t_rtv *rtv);
int				valid_count2(char *str);
int				data_color(char *str, t_color *vec, int k, t_rtv *rtv);
int				data_vector(char *str, t_vector3 *vec, int k, t_rtv *rtv);
int				data_vector_norm(char *str, t_vector3 *vec, int k, t_rtv *rtv);
int				valid_prop(t_prop *object);
void			valid(t_rtv *rtv);
int				close_app(t_rtv *rtv);
void			ft_error(int code);
char			*ft_strjoin_2(char *s1, char *s2);
void			render2(t_rtv *rtv);
void			init_array(t_rtv *rtv);
int				count_items(t_rtv *rtv);
void			malloc_structures(t_rtv *rtv);
void			init_schet(t_rtv *rtv);
void			help_valid_count2(t_rtv *rtv);
void			help_valid_count(t_rtv *rtv);

#endif
