/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozhovnuv <ozhovnuv@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/21 16:49:35 by ozhovnuv          #+#    #+#             */
/*   Updated: 2017/07/03 17:06:50 by ozhovnuv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../rtv1.h"

int			key_action(int button, int zero)
{
	if (button == 53)
		exit(zero);
	return (0);
}

void		mlx_im_create(t_ses_win *wi)
{
	wi->im = (t_image*)malloc(sizeof(t_image));
	wi->im->bpp = 32;
	wi->im->en = 0;
	wi->im->ini = mlx_new_image(wi->mlx, WIDTH, HEIGHT);
	wi->im->data = mlx_get_data_addr(wi->im->ini, &(wi->im->bpp),
	&(wi->im->sizeline), &(wi->im->en));
}

t_ses_win	*mlx_win_im_create(void)
{
	t_ses_win *wi;

	wi = (t_ses_win*)malloc(sizeof(t_ses_win));
	wi->mlx = mlx_init();
	wi->win = mlx_new_window(wi->mlx, WIDTH, HEIGHT, "RTv1");
	mlx_im_create(wi);
	return (wi);
}

void		trace(t_inf *all, t_image *im)
{
	int			y;
	int			x;
	t_vector	dir;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			dir = ray_dir_init(all, x, y);
			if (intersection(all, all->obj, dir) == 1)
			{
				im->data[y * im->sizeline + x * 4] = all->obj_color.b;
				im->data[y * im->sizeline + x * 4 + 1] = all->obj_color.g;
				im->data[y * im->sizeline + x * 4 + 2] = all->obj_color.r;
				im->data[y * im->sizeline + x * 4 + 3] = all->obj_color.a;
			}
			x++;
		}
		y++;
	}
}

int			main(void)
{
	t_inf		*all;
	t_sphere	sphere;
	t_plane		plane_bottom;

	sphere.center = v_new_data(900, 500, 900);
	sphere.radius = 250;
	sphere.color = rgba(99, 234, 255, 0);
	plane_bottom.point = v_new_data(500, -1000, 0);
	plane_bottom.norm = v_new_data(0, 1, 0);
	plane_bottom.color = rgba(232, 112, 12, 0);
	all = (t_inf*)malloc(sizeof(t_inf));
	all->wi = mlx_win_im_create();
	all->cam = v_new_data(900, 500, -1000);
	all->rot = v_new_data(0, 0, 0);
	all->light_num = 2;
	all->light = (t_vector*)malloc(sizeof(t_vector) * all->light_num);
	all->light[0] = v_new_data(350, 600, 100);
	all->light[1] = v_new_data(640, 600, 100);
	lst_first(all->obj, &sphere, SPHERE);
	lst_push(all->obj, &plane_bottom, PLANE);
	trace(all, all->wi->im);
	mlx_put_image_to_window(all->wi->mlx, all->wi->win, all->wi->im->ini, 0, 0);
	mlx_hook(all->wi->win, 2, 5, key_action, 0);
	mlx_hook(all->wi->win, 17, 0, ft_close_window, NULL);
	mlx_loop(all->wi->mlx);
}
