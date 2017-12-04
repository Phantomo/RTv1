/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   additional.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozhovnuv <ozhovnuv@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/03 14:41:01 by ozhovnuv          #+#    #+#             */
/*   Updated: 2017/07/03 14:52:03 by ozhovnuv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../rtv1.h"

int			ft_close_window(void)
{
	exit(0);
	return (0);
}

void		lst_first(t_obj *head, void *obj, int type)
{
	head->obj = obj;
	head->type = type;
	head->next = NULL;
}

void		lst_push(t_obj *head, void *obj, int type)
{
	t_obj	*current;
	t_obj	*right;

	current = head;
	while (current->next != NULL)
	{
		current = current->next;
	}
	right = (t_obj*)malloc(sizeof(t_obj));
	right->obj = obj;
	right->type = type;
	right->next = NULL;
	current->next = right;
}

t_color		rgba(int r, int g, int b, int alpha)
{
	t_color color;

	color.r = r;
	color.g = g;
	color.b = b;
	color.a = alpha;
	return (color);
}
