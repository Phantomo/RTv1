/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozhovnuv <ozhovnuv@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/21 16:58:00 by ozhovnuv          #+#    #+#             */
/*   Updated: 2017/07/03 16:43:04 by ozhovnuv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_H
# define RTV1_H
# include "./lib_vector/libvector.h"
# include <unistd.h>
# include <mlx.h>
# include <stdlib.h>

# define HEIGHT 1000
# define WIDTH 1800
# define FOV 60
# define INV_HEIGHT (1 / (double)HEIGHT)
# define INV_WIDTH (1 / (double)WIDTH)
# define ASP_RATIO (WIDTH / (double)HEIGHT)
# define ANGLE (tan(FOV / 2 * M_PI / 180.0))
# define DEGREE(x) ((double)x * M_PI / 180.0)
# define SIN(x) sin(x * M_PI / 180.0)
# define COS(x) cos(x * M_PI / 180.0)
# define SPHERE 0
# define CYLINDER 1
# define PLANE 2
# define CONE 3
# define DARK_C 220

typedef struct		s_obj
{
	void			*obj;
	int				type;
	struct s_obj	*next;
}					t_obj;

typedef struct		s_image
{
	void			*ini;
	int				h;
	int				w;
	char			*data;
	int				bpp;
	int				sizeline;
	int				en;
}					t_image;

typedef struct		s_ses_win
{
	void			*mlx;
	void			*win;
	int				h;
	int				w;
	t_image			*im;
}					t_ses_win;

typedef struct		s_color
{
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
	unsigned char	a;
}					t_color;

typedef struct		s_inf
{
	t_ses_win		*wi;
	double			t;
	t_obj			*obj;
	t_vector		cam;
	t_vector		*light;
	int				light_num;
	t_color			obj_color;
	t_vector		normal;
	t_vector		hit;
	double			cos;
	t_vector		rot;
}					t_inf;

typedef struct		s_sphere
{
	t_vector		center;
	double			radius;
	t_color			color;
}					t_sphere;

typedef struct		s_cylinder
{
	t_vector		center;
	t_vector		dir;
	double			radius;
	t_color			color;
}					t_cylinder;

typedef struct		s_cone
{
	t_vector		center;
	t_vector		dir;
	double			angle;
	t_color			color;
}					t_cone;

typedef struct		s_plane
{
	t_vector		point;
	t_vector		norm;
	t_color			color;
}					t_plane;

int					intersection(t_inf *all, t_obj *head, t_vector dir);
int					intr_sphere(t_inf *all, t_sphere *s, t_vector ray_pos,
								t_vector dir);
int					intr_cylinder(t_inf *all, t_cylinder *s,
								t_vector ray_pos, t_vector dir);
int					intr_cone(t_inf *all, t_cone *co,
								t_vector ray_pos, t_vector dir);
t_vector			cone_normal(t_vector hit, t_cone *cone);
int					intr_plane(t_inf *all, t_plane *p,
								t_vector ray_pos, t_vector dir);
void				check_obj(t_inf *all, t_obj *cur,
								t_vector start, t_vector dir);
t_color				light_eval(t_inf *all, t_vector hit,
								t_obj *head, t_vector normal);
double				min_allowable(double t1, double t2, t_inf *all);
int					intr_cone(t_inf *all, t_cone *co,
								t_vector ray_pos, t_vector dir);
void				mlx_im_create(t_ses_win *wi);
void				trace(t_inf *all, t_image *im);
t_color				fill_color(t_inf *all, t_color obj_color);
int					ft_close_window(void);
void				lst_first(t_obj *head, void *obj, int type);
void				lst_push(t_obj *head, void *obj, int type);
t_color				rgba(int r, int g, int b, int alpha);
t_vector			ray_dir_init(t_inf *all, int x, int y);
t_vector			rot_x(t_vector dir, double angle);
t_vector			rot_y(t_vector dir, double angle);
t_vector			rot_z(t_vector dir, double angle);
#endif
