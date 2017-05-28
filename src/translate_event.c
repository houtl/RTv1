/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translate_event.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thou <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/19 18:24:05 by thou              #+#    #+#             */
/*   Updated: 2017/05/28 16:30:42 by thou             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void	repere(t_env *e, t_vector *n, t_vector *r)
{
	*n = subvect(&e->cam.pos, &e->cam.dir);
	normalize(&(*n));
	*r = crossvect(n, &(t_vector){0.0, 1.0, 0.0});
	normalize(&(*r));
	e->up = crossvect(&(*r), &(*n));
	normalize(&e->up);
}

static void	translate_pos(int key, t_vector r, t_vector n, t_vector *pos, t_vector up)
{
	t_vector	tmp;

	tmp = *pos;
	if (key == KEY_LEFT)
		*pos = (t_vector){tmp.x + r.x * 10.0,
			tmp.y + r.y * 10.0, tmp.z + r.z * 10.0};
	else if (key == KEY_RIGHT)
		*pos = (t_vector){tmp.x - r.x * 10.0, tmp.y
			- r.y * 10.0, tmp.z - r.z * 10.0};
	else if (key == KEY_UP)
		*pos = (t_vector){tmp.x + up.x * 10.0,
			tmp.y + up.y * 10.0, tmp.z + up.z * 10.0};
	else if (key == KEY_DOWN)
		*pos = (t_vector){tmp.x - up.x * 10.0,
			tmp.y - up.y * 10.0, tmp.z - up.z * 10.0};
	else if (key == KEY_PAD_ADD)
		*pos = (t_vector){tmp.x + n.x * 10.0,
			tmp.y + n.y * 10.0, tmp.z + n.z * 10.0};
	else if (key == KEY_PAD_SUB)
		*pos = (t_vector){tmp.x - n.x * 10.0, tmp.y -
			n.y * 10.0, tmp.z - n.z * 10.0};
}

void		translate(int key, t_env *e)
{
	t_vector	n;
	t_vector	r;

	repere(e, &n, &r);
	if (e->is_obj_selected == 1)
		translate_pos(key, r, n, &e->hit_obj->pos, e->up);
	else
	{
		translate_pos(key, r, n, &e->cam.pos, e->up);
		translate_pos(key, r, n, &e->cam.dir, e->up);
	}
	if (key == KEY_R)
	{
		e->is_obj_selected = 0;
		e->hit_obj = NULL;
	}
}
