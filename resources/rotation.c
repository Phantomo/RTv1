/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozhovnuv <ozhovnuv@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/03 14:31:35 by ozhovnuv          #+#    #+#             */
/*   Updated: 2017/07/03 16:42:09 by ozhovnuv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../rtv1.h"

t_vector	rot_x(t_vector dir, double angle)
{
	t_vector new_dir;

	new_dir.x = dir.x;
	new_dir.y = dir.y * COS(angle) + dir.z * SIN(angle);
	new_dir.z = dir.z * COS(angle) - dir.y * SIN(angle);
	return (new_dir);
}

t_vector	rot_y(t_vector dir, double angle)
{
	t_vector new_dir;

	new_dir.x = dir.x * COS(angle) - dir.z * SIN(angle);
	new_dir.y = dir.y;
	new_dir.z = dir.z * COS(angle) + dir.x * SIN(angle);
	return (new_dir);
}

t_vector	rot_z(t_vector dir, double angle)
{
	t_vector new_dir;

	new_dir.x = dir.x * COS(angle) + dir.y * SIN(angle);
	new_dir.y = dir.y * COS(angle) - dir.x * SIN(angle);
	new_dir.z = dir.z;
	return (new_dir);
}

t_vector	ray_dir_init(t_inf *all, int x, int y)
{
	t_vector	direction;
	t_vector	screen;

	screen.x = (2 * ((x + 0.5) * INV_WIDTH) - 1) * ANGLE * ASP_RATIO;
	screen.y = (1 - 2 * ((y + 0.5) * INV_HEIGHT)) * ANGLE;
	screen.z = 1;
	direction = rot_x(screen, all->rot.x);
	direction = rot_y(direction, all->rot.y);
	direction = rot_z(direction, all->rot.z);
	direction = v_normalize(direction);
	return (direction);
}
