/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_intersection.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozhovnuv <ozhovnuv@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/02 11:34:31 by ozhovnuv          #+#    #+#             */
/*   Updated: 2017/07/02 12:42:52 by ozhovnuv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../rtv1.h"

int			intr_sphere(t_inf *all, t_sphere *s, t_vector ray_pos, t_vector dir)
{
	t_vector	k;
	double		b;
	double		disc;

	k = v_diff(ray_pos, s->center);
	b = s_dot(k, dir);
	disc = b * b - (s_dot(k, k) - s->radius * s->radius);
	if (disc < 0)
		return (0);
	disc = sqrt(disc);
	if (min_allowable(-b + disc, -b - disc, all))
	{
		all->hit = v_sum(ray_pos, v_mult_num(dir, all->t));
		all->normal = v_normalize(v_diff(s->center, all->hit));
		all->obj_color = s->color;
		return (1);
	}
	return (0);
}

double		min_allowable(double t1, double t2, t_inf *all)
{
	double b;

	if (((b = fmin(t1, t2)) > 0.1 && b < all->t) ||
		((b = fmax(t1, t2)) > 0.1 && b < all->t))
	{
		all->t = b - 0.01;
		return (1);
	}
	return (0);
}

int			intr_plane(t_inf *all, t_plane *p, t_vector ray_pos, t_vector dir)
{
	double		t;
	double		denom;
	double		dist;

	p->norm = v_normalize(p->norm);
	dist = s_dot(p->point, p->norm);
	denom = s_dot(dir, p->norm);
	if (fabs(denom) > 0.001)
	{
		t = (dist - s_dot(ray_pos, p->norm)) / denom;
		if (t > 0.001 && t < all->t)
		{
			all->normal = p->norm;
			all->t = t - 0.01;
			all->hit = v_sum(ray_pos, v_mult_num(dir, all->t));
			all->obj_color = p->color;
			return (1);
		}
	}
	return (0);
}

int			intr_cylinder(t_inf *all, t_cylinder *cyl,
			t_vector ray_pos, t_vector dir)
{
	double		a;
	double		b;
	double		c;
	t_vector	dist;
	double		disc;

	cyl->dir = v_normalize(cyl->dir);
	dist = v_diff(ray_pos, cyl->center);
	a = s_dot(dir, dir) - pow(s_dot(dir, cyl->dir), 2);
	b = 2 * (s_dot(dir, dist) - (s_dot(dir, cyl->dir) * s_dot(dist, cyl->dir)));
	c = s_dot(dist, dist) - pow(s_dot(dist, cyl->dir), 2) - pow(cyl->radius, 2);
	disc = b * b - 4 * a * c;
	if (disc < 0)
		return (0);
	disc = sqrt(disc);
	if (min_allowable((-b + disc) / (2 * a), (-b - disc) / (2 * a), all))
	{
		all->hit = v_sum(ray_pos, v_mult_num(dir, all->t));
		a = s_dot(v_diff(all->hit, cyl->center), cyl->dir);
		all->normal = v_normalize(v_diff(v_mult_num(cyl->dir, a),
			v_diff(all->hit, cyl->center)));
		all->obj_color = cyl->color;
		return (1);
	}
	return (0);
}

int			intr_cone(t_inf *all, t_cone *co, t_vector ray_pos, t_vector dir)
{
	double		a;
	double		b;
	double		c;
	t_vector	dist;
	double		disc;

	disc = 1 + pow(tan(co->angle), 2);
	co->dir = v_normalize(co->dir);
	dist = v_diff(ray_pos, co->center);
	a = s_dot(dir, dir) - disc * pow(s_dot(dir, co->dir), 2);
	b = 2 * (s_dot(dir, dist) - disc *
		(s_dot(dir, co->dir) * s_dot(dist, co->dir)));
	c = s_dot(dist, dist) - pow(s_dot(dist, co->dir), 2) * disc;
	disc = b * b - 4 * a * c;
	if (disc < 0)
		return (0);
	disc = sqrt(disc);
	if (min_allowable((-b + disc) / (2 * a), (-b - disc) / (2 * a), all))
	{
		all->hit = v_sum(ray_pos, v_mult_num(dir, all->t));
		all->normal = cone_normal(all->hit, co);
		all->obj_color = co->color;
		return (1);
	}
	return (0);
}
