/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translate_event.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thou <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/19 18:24:05 by thou              #+#    #+#             */
/*   Updated: 2017/05/24 18:07:34 by thou             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void	repere(t_env *e, t_vector *n, t_vector *r)
{
	*n = subvect(&e->cam.pos, &e->cam.dir);
	normalize(&(*n));
	*r = crossvect(n, &(t_vector){0.0, 1.0, 0.0, 0.0});
	normalize(&(*r));
	e->up = crossvect(&(*r), &(*n));
	normalize(&e->up);
}

static void	translate_cam_pos(int key, t_vector r, t_vector n, t_env *e)
{
	t_vector	pos;

	pos = e->cam.pos;
	if (key == KEY_RIGHT)
		e->cam.pos = (t_vector){pos.x + r.x * 10.0, pos.y + r.y * 10.0,
			pos.z + r.z * 10.0, 1.0};
	else if (key == KEY_LEFT)
		e->cam.pos = (t_vector){pos.x - r.x * 10.0, pos.y - r.y * 10.0,
			pos.z - r.z * 10.0, 1.0};
	else if (key == KEY_UP)
		e->cam.pos = (t_vector){pos.x + e->up.x * 10.0, pos.y + e->up.y * 10.0,
			pos.z + e->up.z * 10.0, 1.0};
	else if (key == KEY_DOWN)
		e->cam.pos = (t_vector){pos.x - e->up.x * 10.0, pos.y - e->up.y * 10.0,
			pos.z - e->up.z * 10.0, 1.0};
	else if (key == KEY_PAD_ADD)
		e->cam.pos = (t_vector){pos.x + n.x * 10.0, pos.y + n.y * 10.0, pos.z +
			n.z * 10.0, 1.0};
	else if (key == KEY_PAD_SUB)
		e->cam.pos = (t_vector){pos.x - n.x * 10.0, pos.y - n.y * 10.0, pos.z -
			n.z * 10.0, 1.0};
}

static void	translate_cam_dir(int key, t_vector r, t_vector n, t_env *e)
{
	t_vector	dir;

	dir = e->cam.dir;
	if (key == KEY_RIGHT)
		e->cam.dir = (t_vector){dir.x + r.x * 10.0, dir.y + r.y * 10.0,
			dir.z + r.z * 10.0, 1.0};
	else if (key == KEY_LEFT)
		e->cam.dir = (t_vector){dir.x - r.x * 10.0, dir.y - r.y * 10.0,
			dir.z - r.z * 10.0, 1.0};
	else if (key == KEY_UP)
		e->cam.dir = (t_vector){dir.x + e->up.x * 10.0, dir.y + e->up.y * 10.0,
			dir.z + e->up.z * 10.0, 1.0};
	else if (key == KEY_DOWN)
		e->cam.dir = (t_vector){dir.x - e->up.x * 10.0, dir.y - e->up.y * 10.0,
			dir.z - e->up.z * 10.0, 1.0};
	else if (key == KEY_PAD_ADD)
		e->cam.dir = (t_vector){dir.x + n.x * 10.0, dir.y + n.y * 10.0, dir.z +
			n.z * 10.0, 1.0};
	else if (key == KEY_PAD_SUB)
		e->cam.dir = (t_vector){dir.x - n.x * 10.0, dir.y - n.y * 10.0, dir.z -
			n.z * 10.0, 1.0};
}

static void	translate_obj_pos(int key, t_vector r, t_vector n, t_env *e)
{
	t_obj		*obj;

	if (1 == e->is_obj_selected)
	{
		obj = e->hit_obj;
		if (key == KEY_LEFT)
			e->hit_obj->pos = (t_vector){obj->pos.x + r.x * 10.0,
				obj->pos.y + r.y * 10.0, obj->pos.z + r.z * 10.0, 1.0};
		else if (key == KEY_RIGHT)
			e->hit_obj->pos = (t_vector){obj->pos.x - r.x * 10.0, obj->pos.y
				- r.y * 10.0, obj->pos.z - r.z * 10.0, 1.0};
		else if (key == KEY_UP)
			e->hit_obj->pos = (t_vector){obj->pos.x + e->up.x * 10.0,
				obj->pos.y + e->up.y * 10.0, obj->pos.z + e->up.z * 10.0, 1.0};
		else if (key == KEY_DOWN)
			e->hit_obj->pos = (t_vector){obj->pos.x - e->up.x * 10.0,
				obj->pos.y - e->up.y * 10.0, obj->pos.z - e->up.z * 10.0, 1.0};
		else if (key == KEY_PAD_ADD)
			e->hit_obj->pos = (t_vector){obj->pos.x + n.x * 10.0,
				obj->pos.y + n.y * 10.0, obj->pos.z + n.z * 10.0, 1.0};
		else if (key == KEY_PAD_SUB)
			e->hit_obj->pos = (t_vector){obj->pos.x - n.x * 10.0, obj->pos.y -
				n.y * 10.0, obj->pos.z - n.z * 10.0, 1.0};
	}
}

void		translate(int key, t_env *e)
{
	t_vector	n;
	t_vector	r;

	repere(e, &n, &r);
	if (e->is_obj_selected == 1)
		translate_obj_pos(key, r, n, e);
	else
	{
		translate_cam_pos(key, r, n, e);
		translate_cam_dir(key, r, n, e);
	}
	if (key == KEY_R)
	{
		e->is_obj_selected = 0;
		e->hit_obj = NULL;
	}
	translate_light(key, r, n, e);
}
