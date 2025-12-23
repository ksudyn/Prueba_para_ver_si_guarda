/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksudyn <ksudyn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 11:48:34 by alvaro            #+#    #+#             */
/*   Updated: 2025/12/23 20:10:39 by ksudyn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <MLX42/MLX42.h>
# include "../libft/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <math.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

# define PI 3.141592653589793
# define WIDTH 800
# define HEIGHT 600
# define MAX_OBJ 100
# define EPSILON 1e-6
# define Z __LINE__
# define F __FILE__
#define OFFSET 1e-4

#define NOINTERSECTION -1.0
#define OPAQUE 255

# define ERROR -1
typedef struct s_color
{
	float		r;
	float		g;
	float		b;
}				t_color;

typedef struct s_point
{
	float		x;
	float		y;
	float		z;
}				t_point;

typedef struct s_vector
{
	float		x;
	float		y;
	float		z;
}				t_vec;

typedef enum e_type
{
	ER = 0,
	PL,
	SP,
	CY,
	CM,
	AM,
	LG,
}				t_type;

typedef struct s_obj
{
	t_type		type;
	t_point		position;
	t_color		color;
	t_vec		normal;
	double		diameter;
	double		height;
}				t_obj;

typedef struct s_camera
{
	bool		status;
	t_point		position;
	t_vec		forward;
	t_vec		up;
	t_vec		right;
	double		scale;
	double		ratio;
}				t_camera;

typedef struct s_ambient
{
	bool		status;
	double		brightness;
	t_color		color;
}				t_ambient;

typedef struct s_light
{
	bool		status;
	t_point		position;
	double		brightness;
}				t_light;

typedef struct s_ray
{
	t_point		origin;
	t_vec		direction;
}				t_ray;

typedef struct s_intr
{
	t_point		position;
	t_vec		normal;
	t_obj		*obj;
}				t_intr;

typedef struct s_gl
{
	mlx_t		*window;
	mlx_image_t	*image;
}				t_gl;

typedef struct s_scene
{
	t_gl		gl;
	t_camera	camera;
	t_ambient	ambient;
	t_light		light;
	int			obj_num;
	t_obj		obj[MAX_OBJ];
}				t_scene;

typedef struct s_parse
{
	char		**tokens;
	t_type		type;
	t_point		p;
	t_vec		v;
	float		val;
	float		height;
	t_color		c;
}				t_parse;

/* ===================== */
/* ===== ERRORS ========= */
/* ===================== */

void			ft_error(char *file, int lineno, char **msg);
void			er_close(int fd);

/* ===================== */
/* ===== PARSE ========= */
/* ===================== */

char			**split_line_by_space(char *line);
t_color			parse_color(char *str, bool *error, bool free_str);
t_vec			parse_vector(char *str, bool *error, bool free_str);
t_point			parse_point(char *str, bool *error, bool free_str);
int				parse_int(char *str, bool *error, bool free_str);
float			parse_float(char *str, bool *error, bool free_str);

bool			is_rt(char *file);
bool			ft_parse(char *filename, t_scene *scene);
void			create_scene_object(t_scene *scene, t_parse parse_data);

bool			assign_values_ambient(t_parse *parse);
bool			assign_values_camera(t_parse *parse);
bool			assign_values_light_or_sphere(t_parse *parse);
bool			assign_values_cylinder_or_plane(t_parse *parse);
bool			assign_values(t_parse *parse);

bool			read_file(t_scene *scene, int fd);
t_parse			parse_object_type(char *token);

/* ===================== */
/* ===== MATH VEC ====== */
/* ===================== */

t_vec			vector_zero(void);
double			module(t_vec vector);
t_vec			normalize(t_vec vector);
double			scalar_p(t_vec a, t_vec b);
t_vec			vectorial_p(t_vec a, t_vec b);
t_vec			add_vectors(t_vec a, t_vec b);
t_vec			sub_vectors(t_vec a, t_vec b);
t_vec			scale_vector(t_vec vector, double scale);
t_vec			flip_vector(t_vec vector);

/* ===================== */
/* ===== MATH POINT ==== */
/* ===================== */

t_vec			sub_points(t_point a, t_point b);
t_point			vectors_point(t_point origin, t_vec vector);
double			euclidean_distance(t_point a, t_point b);

/* ===================== */
/* ===== NORMALS ======= */
/* ===================== */

t_vec			get_normal(t_intr intr, t_ray ray);

/* ===================== */
/* ===== CAMERA ======== */
/* ===================== */

t_camera		create_camera(t_point position, t_vec forward, double fov,
					bool raw);

/* ===================== */
/* ===== LIGHT ========= */
/* ===================== */

t_light			create_light(double brightness, t_point position, bool enabled);
t_ambient		create_ambient(t_color color, double brightness, bool enabled);

/* ===================== */
/* ===== OBJECTS ======= */
/* ===================== */

t_obj			create_plane(t_point position, t_vec normal, t_color color);
t_obj			create_sphere(t_point position, float radius, t_color color);
t_obj			create_cylinder(t_point position, t_vec axis, float values[2],
					t_color color);

/* ray */
t_ray		get_ray(t_camera cam, int x, int y);
void		init_shadow_ray(t_light light, t_ray *ray, t_intr intr);

/* intersect */
t_intr		get_intersection(t_scene *scene, t_ray ray);

/* normals */
t_vec		get_normal(t_intr intr, t_ray ray);

/* lighting */
t_color		get_lighting(t_scene *scene, t_intr intr);

/* pixel */
void		put_pixel(t_scene *scene, int x, int y, t_color c);
uint32_t	color_to_int(t_color c);

/* raytrace */
void		raytrace_scene(t_scene *scene);


					
#endif
