/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translate_light.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thou <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/19 18:24:19 by thou              #+#    #+#             */
/*   Updated: 2017/05/19 18:24:21 by thou             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void	translate_light_1(int key, t_vector r, t_vector n, t_env *e)
{
	t_obj	light;

	if (e->light[0] == NULL)
		return ;
	light = *e->light[0];
	if (key == KEY_W)
		e->light[0]->pos = (t_vector){light.pos.x + r.x * 10.0,
			light.pos.y + r.y * 10.0, light.pos.z + r.z * 10.0, 1.0};
	else if (key == KEY_Q)
		e->light[0]->pos = (t_vector){light.pos.x - r.x * 10.0,
			light.pos.y - r.y * 10.0, light.pos.z - r.z * 10.0, 1.0};
	else if (key == KEY_E)
		e->light[0]->pos = (t_vector){light.pos.x + e->up.x * 10.0,
			light.pos.y + e->up.y * 10.0, light.pos.z + e->up.z * 10.0, 1.0};
	else if (key == KEY_D)
		e->light[0]->pos = (t_vector){light.pos.x - e->up.x * 10.0,
			light.pos.y - e->up.y * 10.0, light.pos.z - e->up.z * 10.0, 1.0};
	else if (key == KEY_A)
		e->light[0]->pos = (t_vector){light.pos.x + n.x * 10.0,
			light.pos.y + n.y * 10.0, light.pos.z + n.z * 10.0, 1.0};
	else if (key == KEY_S)
		e->light[0]->pos = (t_vector){light.pos.x - n.x * 10.0,
			light.pos.y - n.y * 10.0, light.pos.z - n.z * 10.0, 1.0};
}

static void	translate_light_2(int key, t_vector r, t_vector n, t_env *e)
{
	t_obj light;

	if (e->light[1] == NULL)
		return ;
	light = *e->light[1];
	if (key == KEY_O)
		e->light[1]->pos = (t_vector){light.pos.x + r.x * 10.0,
			light.pos.y + r.y * 10.0, light.pos.z + r.z * 10.0, 1.0};
	else if (key == KEY_I)
		e->light[1]->pos = (t_vector){light.pos.x - r.x * 10.0,
			light.pos.y - r.y * 10.0, light.pos.z - r.z * 10.0, 1.0};
	else if (key == KEY_U)
		e->light[1]->pos = (t_vector){light.pos.x + e->up.x * 10.0,
			light.pos.y + e->up.y * 10.0, light.pos.z + e->up.z * 10.0, 1.0};
	else if (key == KEY_J)
		e->light[1]->pos = (t_vector){light.pos.x - e->up.x * 10.0,
			light.pos.y - e->up.y * 10.0, light.pos.z - e->up.z * 10.0, 1.0};
	else if (key == KEY_K)
		e->light[1]->pos = (t_vector){light.pos.x + n.x * 10.0,
			light.pos.y + n.y * 10.0, light.pos.z + n.z * 10.0, 1.0};
	else if (key == KEY_L)
		e->light[1]->pos = (t_vector){light.pos.x - n.x * 10.0,
			light.pos.y - n.y * 10.0, light.pos.z - n.z * 10.0, 1.0};
}

void	translate_light(int key, t_vector r, t_vector n, t_env *e)
{
	translate_light_1(key, r, n, e);
	translate_light_2(key, r, n, e);
}
