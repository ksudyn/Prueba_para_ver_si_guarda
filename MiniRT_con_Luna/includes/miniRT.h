/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksudyn <ksudyn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 11:48:34 by alvaro            #+#    #+#             */
/*   Updated: 2025/12/29 18:43:08 by ksudyn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "../libft/libft.h"
# include "../minilibx-linux/mlx.h"
# include <errno.h>
# include <fcntl.h>
# include <math.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <string.h>
# include <unistd.h>

# define PI 3.141592653589793
# define WIDTH 800
# define HEIGHT 600
# define MAX_OBJ 100
# define EPSILON 1e-6
# define Z __LINE__
# define F __FILE__
# define OFFSET 1e-4

# define NOINTERSECTION -1.0

# define ERROR -1
// WIDTH y HEIGHT → tamaño de la ventana.
// MAX_OBJ → máximo número de objetos en la escena.
// EPSILON y OFFSET → para evitar problemas de precisión en intersecciones.
// NOINTERSECTION → valor que indica que un rayo no chocó con ningún objeto.

typedef struct s_color//RGB
{
	float		r;
	float		g;
	float		b;
}				t_color;

typedef struct s_point//posición de cámara, luz u objetos.
{
	float		x;
	float		y;
	float		z;
}				t_point;

typedef struct s_vector//direcciones, normales, vectores de cámara
{
	float		x;
	float		y;
	float		z;
}				t_vec;

typedef enum e_type//identifica el tipo: plano, esfera, cilindro, cámara, luz, ambiente.
{
	TYPE_ERROR = 0,
	PLANE,
	SPHERE,
	CYLINDER,
	CAMERA,
	AMBIENT,
	LIGHT,
}				t_type;

typedef struct s_obj//representa un objeto en la escena, con posición, color, normal y dimensiones.
{
	t_type		type;
	t_point		position;
	t_color		color;
	t_vec		normal;
	double		diameter;
	double		height;
}				t_obj;

typedef struct s_camera//posición, dirección y vectores para proyectar la imagen.
{
	bool		status;
	t_point		position;
	t_vec		forward;
	t_vec		up;
	t_vec		right;
	double		scale;
	double		ratio;
}				t_camera;

typedef struct s_ambient//brillo global y color
{
	float		ratio;
	bool		status;
	double		brightness;
	t_color		color;
}				t_ambient;

typedef struct s_light//punto y brillo.
{
	bool		status;
	t_point		position;
	double		brightness;
}				t_light;

typedef struct s_ray//rayo desde cámara
{
	t_point		origin;
	t_vec		direction;
}				t_ray;

typedef struct s_intr//información de intersección: punto de contacto, normal y objeto
{
	t_point		position;
	t_vec		normal;
	t_obj		*obj;
}				t_intr;

typedef struct s_gl//manejo de MinilibX: ventana, imagen y datos de píxeles.
{
	void		*mlx_ptr;
	void		*win_ptr;
	void		*img_ptr;
	int			*img_data;
	int			width;
	int			height;
}				t_gl;

typedef struct s_scene//agrupa todo: cámara, luz, ambient, objetos.
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
void			ft_error_close(int fd);

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

bool			check_format(t_scene *scene, char **tokens, t_type type,
					bool *error);

/* ===================== */
/* ===== MATH VEC ====== */
/* ===================== */

t_vec			vector_zero(void);
bool			is_zero_vector(t_vec v);
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
t_ray			get_ray(t_camera cam, int x, int y);
void			init_shadow_ray(t_light light, t_ray *ray, t_intr intr);

/* intersect */
t_intr			get_intersection(t_scene *scene, t_ray ray);

/* lighting */
t_color			get_lighting(t_scene *scene, t_intr intr);

/* pixel */
void			put_pixel(t_scene *scene, int x, int y, t_color c);
int				color_to_int(t_color c);

/* raytrace */
void			raytrace_scene(t_scene *scene);

void			free_arg(char **arg);
bool			check_zero_vector(t_vec v, bool *error);

double			ft_atolf(char *str);
int				ft_arr_len(char **arr);
char			**read_next_line_tokens(int fd);

// parse
bool			check_format(t_scene *s, char **toks, t_type type, bool *error);
bool			is_rt(char *file);

// raytracing
double			compute_sphere_intersection(t_ray ray, t_obj obj);
double			compute_plane_intersection(t_ray ray, t_obj obj);
double			compute_cylinder_intersection(t_ray ray, t_obj obj);

#endif
