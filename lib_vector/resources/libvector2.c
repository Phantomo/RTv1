/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libvector2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozhovnuv <ozhovnuv@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/02 13:30:10 by ozhovnuv          #+#    #+#             */
/*   Updated: 2017/07/02 14:15:24 by ozhovnuv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libvector.h"

t_vector	v_mult(t_vector a, t_vector b)
{
	t_vector new;

	new.x = a.y * b.z - a.z * b.z;
	new.y = a.z * b.x - a.x * b.z;
	new.z = a.x * b.y - a.y * b.x;
	return (new);
}

t_vector	v_mult_num(t_vector a, double b)
{
	t_vector new;

	new.x = a.x * b;
	new.y = a.y * b;
	new.z = a.z * b;
	return (new);
}

double		s_dot(t_vector a, t_vector b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

t_vector	v_normalize(t_vector a)
{
	t_vector new;

	new.x = a.x / v_magnitude(a);
	new.y = a.y / v_magnitude(a);
	new.z = a.z / v_magnitude(a);
	return (new);
}

double		s_cos(t_vector a, t_vector b)
{
	return (s_dot(a, b) / (v_magnitude(a) * v_magnitude(b)));
}
