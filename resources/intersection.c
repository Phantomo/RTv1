/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozhovnuv <ozhovnuv@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/02 11:31:25 by ozhovnuv          #+#    #+#             */
/*   Updated: 2017/07/03 14:51:21 by ozhovnuv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../rtv1.h"

t_color		fill_color(t_inf *all, t_color obj_color)
{
	double	c_spot;

	c_spot = 0.9 * pow(all->cos, 20) + 0.1 * all->cos;
	obj_color.a += DARK_C * (1 - all->cos) / all->light_num;
	obj_color.r += (255 - obj_color.r) * c_spot;
	obj_color.g += (255 - obj_color.g) * c_spot;
	obj_color.b += (255 - obj_color.b) * c_spot;
	return (obj_color);
}

void		check_obj(t_inf *all, t_obj *cur, t_vector start, t_vector dir)
{
	all->t = INFINITY;
	while (cur != NULL)
	{
		if (cur->type == SPHERE)
			intr_sphere(all, (t_sphere*)cur->obj, start, dir);
		else if (cur->type == CYLINDER)
			intr_cylinder(all, (t_cylinder*)cur->obj, start, dir);
		else if (cur->type == CONE)
			intr_cone(all, (t_cone*)cur->obj, start, dir);
		else if (cur->type == PLANE)
			intr_plane(all, (t_plane*)cur->obj, start, dir);
		cur = cur->next;
	}
}

t_color		light_eval(t_inf *all, t_vector hit, t_obj *head, t_vector normal)
{
	int			i;
	t_obj		*cur;
	t_vector	dir;
	t_color		obj_color;

	obj_color = all->obj_color;
	i = 0;
	while (i < all->light_num)
	{
		cur = head;
		dir = v_normalize(v_diff(all->light[i], hit));
		check_obj(all, cur, hit, dir);
		all->cos = fabs(s_cos(v_diff(hit, all->light[i]), normal));
		if (v_magnitude(v_diff(hit, all->light[i])) < all->t)
			obj_color = fill_color(all, obj_color);
		else
			obj_color.a += DARK_C / all->light_num;
		i++;
	}
	return (obj_color);
}

int			intersection(t_inf *all, t_obj *head, t_vector dir)
{
	t_obj	*cur;

	cur = head;
	check_obj(all, cur, all->cam, dir);
	if (all->t != INFINITY)
	{
		all->obj_color = light_eval(all, all->hit, all->obj, all->normal);
		return (1);
	}
	return (0);
}

t_vector	cone_normal(t_vector hit, t_cone *cone)
{
	t_vector	norm;
	double		tmp;
	t_vector	c;

	norm = v_diff(hit, cone->center);
	tmp = s_dot(norm, cone->dir);
	c = v_mult_num(cone->dir, tmp);
	c = v_mult_num(c, (1 + pow(tan(cone->angle), 2)));
	norm = v_normalize(v_diff(c, norm));
	return (norm);
}
