/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaiz-lo <asaiz-lo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 11:48:34 by alvaro            #+#    #+#             */
/*   Updated: 2025/11/06 12:15:19 by asaiz-lo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "./MLX42/include/MLX42/MLX42.h"
# include "./libft/libft.h"

# include <math.h>
# include <stdbool.h>
# include <stdlib.h>
# include <unistd.h>
# include <errno.h>
# include <string.h>
# include <stdio.h>
# include <fcntl.h>

# ifndef HEIGHT
#  define HEIGHT 1080
# endif
# ifndef WIDTH
#  define WIDTH 1920
# endif

# define MAX_OBJ 100
# define PI M_PI

# define ERROR -1
# define EXIT_FAILURE 1
# define SUCCESS 1
# define Z __LINE__
# define F __FILE__

# define BRIGHTNESS 1
# define EPSILON 1e-6
# define OPAQUE 0x000000FF
# define OFFSET 0.01
# define NOINTERSECTION INFINITY

# define ATT_IMG_ERR "minirt: failed to attach image to window in a graph lib"
# define INIT_WINDOW_ERR "minirt: failed to connect to a graphic library"
# define INIT_IMAGE_ERR "minirt: failed to created image in a graphic library"

typedef struct s_color
{
	float	r;
	float	g;
	float	b;
}					t_color;

// maths.c

typedef struct s_point
{
	float	x;
	float	y;
	float	z;
}					t_point;

typedef struct s_vector
{
	float	x;
	float	y;
	float	z;
}					t_vec;

// objects.c

typedef enum e_type
{
	ER = 0,
	PL,
	SP,
	CY,
	CM,
	AM,
	LG,
}					t_type;

typedef struct s_obj
{
	t_type			type;
	t_point			position;
	t_color			color;
	t_vec			normal;
	double			diameter;
	double			height;
}					t_obj;

typedef struct s_camera
{
	bool			status;
	t_point			position;
	t_vec			forward;
	t_vec			up;
	t_vec			right;
	double			scale;
	double			ratio;
}					t_camera;

typedef struct s_ambient
{
	bool			status;
	double			brightness;
	t_color			color;
}					t_ambient;

typedef struct s_light
{
	bool			status;
	t_point			position;
	double			brightness;
}					t_light;

// rays.c

typedef struct s_ray
{
	t_point			origin;
	t_vec			direction;
}					t_ray;

typedef struct s_intr
{
	t_point			position;
	t_vec			normal;
	t_obj			*obj;
}					t_intr;

// render

typedef struct s_gl
{
	mlx_t			*window;
	mlx_image_t		*image;
}					t_gl;

// Scene

typedef struct s_scene
{
	t_gl			gl;
	t_camera		camera;
	t_ambient		ambient;
	t_light			light;
	int				obj_num;
	t_obj			obj[MAX_OBJ];
}					t_scene;

// Parse

typedef struct s_parse
{
	char			**tokens;
	t_type			type;
	t_point			p;
	t_vec			v;
	float			val;
	float			height;
	t_color			c;
}					t_parse;

// ft_error.c

void		er_close(int fd);
void		err(char *file, int lineno, char **msg);
void		puterr(char *str);

// mem.c

void		free_arr(char **arr);

/*
 *        ooooooooo.                                                 
 *        `888   `Y88.                                               
 *         888   .d88'  .oooo.   oooo d8b  .oooo.o  .ooooo.  oooo d8b
 *         888ooo88P'  `P  )88b  `888""8P d88(  "8 d88' `88b `888""8P
 *         888          .oP"888   888     `"Y88b.  888ooo888  888    
 *         888         d8(  888   888     o.  )88b 888    .o  888    
 *        o888o        `Y888""8o d888b    8""888P' `Y8bod8P' d888b   
*/

float		get_float(char *str, bool *err, bool free);
int			get_int(char *str, bool *err, bool free);
t_point		get_point(char *str, bool *err, bool free);
t_vec		get_vector(char *str, bool *err, bool free);
t_color		get_color(char *str, bool *err, bool free);

bool		add_val_am(t_parse *p);
bool		add_val_cm(t_parse *p);
bool		add_val_lg_or_sp(t_parse *p);
bool		add_val_cy_or_pl(t_parse *p);

bool		check_format(t_scene *s, char **toks, t_type type, bool *err);
bool		is_rt(char *file);
bool		check_zero_vector(t_vec v, bool *error);

bool		get_vals(char **tokens, t_parse *par);
t_parse		get_type(char *tok);
void		create_object(t_scene *s, t_parse p);
bool		read_file(t_scene *s, int fd);
bool		parse(char *file, t_scene *s);

char		**isspace_split(char *str);
double		ft_atolf(char *str);

/*
 *  ooooo                 .                     
 *  `888'               .o8                     
 *   888  ooo. .oo.   .o888oo  .ooooo.  oooo d8b
 *   888  `888P"Y88b    888   d88' `88b `888""8P
 *   888   888   888    888   888ooo888  888    
 *   888   888   888    888 . 888    .o  888    
 *  o888o o888o o888o   "888" `Y8bod8P' d888b    
*/

// print_utils.c

char		*get_type_str(t_obj o);
void		print_vector(t_vec v);
void		print_point(t_point p);
void		print_color(t_color c);

// rotation.c

t_camera	get_rotation_cam(t_scene *s, bool *err);
t_vec		get_rotation_obj(t_scene *s, int idx, bool *err);
t_vec		rotate_vector(t_vec v, float rad, char axis);

// change_obj_utils.c

bool		change_pl(t_scene *s, int idx);
bool		change_sp(t_scene *s, int idx);
bool		change_cy(t_scene *s, int idx);
bool		change_obj_val(t_scene *s, int idx);

// take_input.c

bool		change_cam(t_scene *s);
bool		change_light(t_scene *s);
bool		change_obj(t_scene *s);
bool		take_input(t_scene *scene);
int			get_index(void);

/*
 *		                                .   oooo                
 *		                              .o8   `888                
 *		ooo. .oo.  .oo.    .oooo.   .o888oo  888 .oo.    .oooo.o
 *		`888P"Y88bP"Y88b  `P  )88b    888    888P"Y88b  d88(  "8
 *		 888   888   888   .oP"888    888    888   888  `"Y88b. 
 *		 888   888   888  d8(  888    888 .  888   888  o.  )88b
 *		o888o o888o o888o `Y888""8o   "888" o888o o888o 8""888P'
*/

// normal.c

t_vec		get_normal(t_intr intr, t_ray ray);

// vector.c

double		module(t_vec vector);
t_vec		normalize(t_vec vector);
t_vec		scale_vector(t_vec vector, double scale);
t_vec		flip_vector(t_vec vector);
t_vec		sub_points(t_point a, t_point b);

// 2vectors.c

double		scalar_p(t_vec a, t_vec b);
t_vec		vectorial_p(t_vec a, t_vec b);
t_vec		add_vectors(t_vec a, t_vec b);
t_vec		sub_vectors(t_vec a, t_vec b);
t_point		vectors_point(t_point o, t_vec v);

// points.c

t_point		add_points_p(t_point a, t_point b);
double		euclidean_distance(t_point a, t_point b);

/*
 *		
 *		           .o8           o8o                         .           
 *		          "888           `"'                       .o8           
 *		 .ooooo.   888oooo.     oooo  .ooooo.   .ooooo.  .o888oo  .oooo.o
 *		d88' `88b  d88' `88b    `888 d88' `88b d88' `"Y8   888   d88(  "8
 *		888   888  888   888     888 888ooo888 888         888   `"Y88b. 
 *		888   888  888   888     888 888    .o 888   .o8   888 . o.  )88b
 *		`Y8bod8P'  `Y8bod8P'     888 `Y8bod8P' `Y8bod8P'   "888" 8""888P'
 *		                         888                                     
 *		                     .o. 88P                                     
 *		                     `Y888P                                      
*/

// cylinder.c

t_obj		create_cylinder(t_point p, t_vec v, float rlen[2], t_color color);
double		compute_cylinder_intersection(t_ray ray, t_obj obj);

// plane.c

t_obj		create_plane(t_point point, t_vec v, t_color c);
double		compute_plane_intersection(t_ray ray, t_obj obj);

// sphere.c

t_obj		create_sphere(t_point p, float r, t_color c);
double		compute_sphere_intersection(t_ray ray, t_obj obj);

// camera

t_camera	create_camera(t_point pos, t_vec forw, double scale, bool raw);

// lights

t_light		create_light(double brightness, t_point pos, bool on);
t_ambient	create_ambient(t_color c, double brightness, bool on);

/*
 *		oooo d8b  .oooo.   oooo    ooo  .oooo.o
 *		`888""8P `P  )88b   `88.  .8'  d88(  "8
 *		 888      .oP"888    `88..8'   `"Y88b. 
 *		 888     d8(  888     `888'    o.  )88b
 *		d888b    `Y888""8o     .8'     8""888P'
 *		                   .o..P'              
 *		                   `Y8P'               
*/

t_color		get_ambient(t_scene *scene, t_intr intrs);

// difuse.c

void		init_shadow_ray(t_light light, t_ray *ray, t_intr intrs);
double		get_intensity(t_vec direction, t_vec normal);
t_color		get_diffuse(t_scene *scene, t_intr intrs);

// intersects.c

t_intr		get_intr(t_scene *scene, t_ray ray);

// light.c

t_color		add_light(t_scene *scene, t_intr intr);

// rays.c

t_ray		get_ray(t_camera camera, int x, int y);
bool		is_shadowed(t_scene *scene, t_ray ray, t_intr intrs);

/*
 *		                                     .o8                    
 *		                                    "888                    
 *		oooo d8b  .ooooo.  ooo. .oo.    .oooo888   .ooooo.  oooo d8b
 *		`888""8P d88' `88b `888P"Y88b  d88' `888  d88' `88b `888""8P
 *		 888     888ooo888  888   888  888   888  888ooo888  888    
 *		 888     888    .o  888   888  888   888  888    .o  888    
 *		d888b    `Y8bod8P' o888o o888o `Y8bod88P" `Y8bod8P' d888b   
*/

//mlx_utils.c

void		key_press(mlx_key_data_t keycode, void *param);
void		cross_click(void *param);
uint32_t	get_raw(t_color color);
void		put_pixel(t_scene *scene, int x, int y, t_color color);

// render_img.c

void		display_image(t_scene *scene);
void		compute_image(t_scene *scene);
void		init_graphic_library(t_scene *scene);

/*
 *		                .    o8o  oooo          
 *		              .o8    `"'  `888          
 *		oooo  oooo  .o888oo oooo   888   .oooo.o
 *		`888  `888    888   `888   888  d88(  "8
 *		 888   888    888    888   888  `"Y88b. 
 *		 888   888    888 .  888   888  o.  )88b
 *		 `V88V"V8P'   "888" o888o o888o 8""888P'
*/

t_color		get_pixel_color(t_scene *scene, int x, int y);

/*
 *       ooooooooooooo                        .                     
 *       8'   888   `8                      .o8                     
 *            888       .ooooo.   .oooo.o .o888oo  .ooooo.  oooo d8b
 *            888      d88' `88b d88(  "8   888   d88' `88b `888""8P
 *            888      888ooo888 `"Y88b.    888   888ooo888  888    
 *            888      888    .o o.  )88b   888 . 888    .o  888    
 *           o888o     `Y8bod8P' 8""888P'   "888" `Y8bod8P' d888b   
*/

//void		print_scene(t_scene s);

#endif
