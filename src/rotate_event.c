/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_event.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thou <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/19 18:23:53 by thou              #+#    #+#             */
/*   Updated: 2017/05/21 14:17:48 by thou             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

#define POS e->cam->pos
#define DIR e->cam->dir
#define ROT e->hit_obj->rot

static void	rotate_cam_pos(int key, t_env *e)
{
	if (e->is_obj_selected == 1)
		return ;
	if (key == KEY_PAD_1)
		e->cam->pos = (t_vector){POS.x * cosf(0.13) + POS.y * sinf(-0.13),
			POS.x * sinf(0.13) + POS.y * cosf(0.13), POS.z, 1.0};
	if (key == KEY_PAD_2)
		e->cam->pos = (t_vector){POS.x * cosf(0.13) + POS.y * sinf(0.13),
			POS.x * sinf(-0.13) + POS.y * cosf(0.13), POS.z, 1.0};
	if (key == KEY_PAD_4)
		e->cam->pos = (t_vector){POS.x * cosf(0.13) + POS.z * sinf(0.13), POS.y,
			POS.x * sinf(-0.13) + POS.z * cosf(0.13), 1.0};
	if (key == KEY_PAD_5)
		e->cam->pos = (t_vector){POS.x * cosf(0.13) + POS.z * sinf(-0.13),
			POS.y, POS.x * sinf(0.13) + POS.z * cosf(0.13), 1.0};
	if (key == KEY_PAD_7)
		e->cam->pos = (t_vector){POS.x, POS.y * cosf(0.13) + POS.z *
			sinf(-0.13), POS.y * sinf(0.13) + POS.z * cosf(0.13), 1.0};
	if (key == KEY_PAD_8)
		e->cam->pos = (t_vector){POS.x, POS.y * cosf(0.13) + POS.z * sinf(0.13),
			POS.y * sinf(-0.13) + POS.z * cosf(0.13), 1.0};
}

static void	rotate_cam_dir(int key, t_env *e)
{
	if (e->is_obj_selected == 1)
		return ;
	if (key == KEY_PAD_1)
		e->cam->dir = (t_vector){DIR.x * cosf(0.13) + DIR.y * sinf(-0.13),
			DIR.x * sinf(0.13) + DIR.y * cosf(0.13), DIR.z, 1.0};
	if (key == KEY_PAD_2)
		e->cam->dir = (t_vector){DIR.x * cosf(0.13) + DIR.y * sinf(0.13),
			DIR.x * sinf(-0.13) + DIR.y * cosf(0.13), DIR.z, 1.0};
	if (key == KEY_PAD_4)
		e->cam->dir = (t_vector){DIR.x * cosf(0.13) + DIR.z * sinf(0.13),
			DIR.y, DIR.x * sinf(-0.13) + DIR.z * cosf(0.13), 1.0};
	if (key == KEY_PAD_5)
		e->cam->dir = (t_vector){DIR.x * cosf(0.13) + DIR.z * sinf(-0.13),
			DIR.y, DIR.x * sinf(0.13) + DIR.z * cosf(0.13), 1.0};
	if (key == KEY_PAD_7)
		e->cam->dir = (t_vector){DIR.x, DIR.y * cosf(0.13) + DIR.z *
			sinf(-0.13), DIR.y * sinf(0.13) + DIR.z * cosf(0.13), 1.0};
	if (key == KEY_PAD_8)
		e->cam->dir = (t_vector){DIR.x, DIR.y * cosf(0.13) + DIR.z * sinf(0.13),
			DIR.y * sinf(-0.13) + DIR.z * cosf(0.13), 1.0};
}

static void	rotate_selected_obj_rot(int key, t_env *e)
{
	if (e->is_obj_selected == 1)
	{
		if (key == KEY_PAD_1)
			e->hit_obj->rot = (t_vector){ROT.x * cosf(0.13) + ROT.y *
				sinf(-0.13), ROT.x * sinf(0.13) + ROT.y * cosf(0.13),
					ROT.z, 0.0};
		if (key == KEY_PAD_2)
			e->hit_obj->rot = (t_vector){ROT.x * cosf(0.13) + ROT.y * sinf(0.13)
				, ROT.x * sinf(-0.13) + ROT.y * cosf(0.13), ROT.z, 0.0};
		if (key == KEY_PAD_4)
			e->hit_obj->rot = (t_vector){ROT.x * cosf(0.13) + ROT.z * sinf(0.13)
				, ROT.y, ROT.x * sinf(-0.13) + ROT.z * cosf(0.13), 0.0};
		if (key == KEY_PAD_5)
			e->hit_obj->rot = (t_vector){ROT.x * cosf(0.13) + ROT.z *
				sinf(-0.13), ROT.y, ROT.x * sinf(0.13) + ROT.z * cosf(0.13),
					0.0};
		if (key == KEY_PAD_7)
			e->hit_obj->rot = (t_vector){ROT.x, ROT.y * cosf(0.13) + ROT.z *
				sinf(-0.13), ROT.y * sinf(0.13) + ROT.z * cosf(0.13), 0.0};
		if (key == KEY_PAD_8)
			e->hit_obj->rot = (t_vector){ROT.x, ROT.y * cosf(0.13) + ROT.z *
				sinf(0.13), ROT.y * sinf(-0.13) + ROT.z * cosf(0.13), 0.0};
	}
}

void		rotate_camera(int key, t_env *e)
{
	rotate_cam_pos(key, e);
	rotate_cam_dir(key, e);
	rotate_selected_obj_rot(key, e);
}
