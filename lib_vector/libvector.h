/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libvector.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozhovnuv <ozhovnuv@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/20 20:36:55 by ozhovnuv          #+#    #+#             */
/*   Updated: 2017/07/03 15:41:59 by ozhovnuv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBVECTOR_H
# define LIBVECTOR_H
# include <math.h>

typedef struct	s_vector
{
	double		x;
	double		y;
	double		z;
}				t_vector;

t_vector		v_sum(t_vector a, t_vector b);
t_vector		v_diff(t_vector a, t_vector b);
t_vector		v_mult(t_vector a, t_vector b);
t_vector		v_mult_num(t_vector a, double b);
double			s_dot(t_vector a, t_vector b);
t_vector		v_normalize(t_vector a);
double			s_cos(t_vector a, t_vector b);
double			v_magnitude(t_vector a);
void			v_print(t_vector a);
t_vector		v_new_data(double x, double y, double z);
void			v_data(t_vector *v, double a, double b, double c);
int				v_compare(t_vector a, t_vector b);

#endif
