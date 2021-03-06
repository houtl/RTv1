/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thou <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/19 18:23:43 by thou              #+#    #+#             */
/*   Updated: 2017/05/28 15:12:44 by thou             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	current_ray(double x, double y, t_env *e, t_ray *ray)
{
	double	xindent;
	double	yindent;

	e->cam.normal = subvect(&e->cam.pos, &e->cam.dir);
	normalize(&e->cam.normal);
	e->cam.right = crossvect(&e->cam.normal, &e->up);
	normalize(&e->cam.right);
	e->cam.up = crossvect(&e->cam.right, &e->cam.normal);
	xindent = (WIDTH - x * 2.0) / HEIGHT;
	yindent = (HEIGHT - y * 2.0) / WIDTH;
	ray->pos.x = e->cam.pos.x;
	ray->pos.y = e->cam.pos.y;
	ray->pos.z = e->cam.pos.z;
	ray->dir.x = FOC * e->cam.normal.x + yindent * e->cam.up.x + xindent *
		e->cam.right.x;
	ray->dir.y = FOC * e->cam.normal.y + yindent * e->cam.up.y + xindent *
		e->cam.right.y;
	ray->dir.z = FOC * e->cam.normal.z + yindent * e->cam.up.z + xindent *
		e->cam.right.z;
	normalize(&ray->dir);
}
