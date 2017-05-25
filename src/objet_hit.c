/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objet_hit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thou <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/19 18:23:31 by thou              #+#    #+#             */
/*   Updated: 2017/05/25 18:15:11 by thou             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

#define INIT 0
#define ADD 1
#define SUM 2

static void		sum_color(double sum[3], t_color *c, double p, int flag)
{
	if (INIT == flag)
	{
		sum[0] = 0.0;
		sum[1] = 0.0;
		sum[2] = 0.0;
	}
	if (ADD == flag)
	{
		sum[0] += (double)c->r;
		sum[1] += (double)c->g;
		sum[2] += (double)c->b;
	}
	if (SUM == flag)
	{
		c->r = sum[0] / p;
		c->g = sum[1] / p;
		c->b = sum[2] / p;
	}
}

static void		check_t(t_env *env, double sum[3], t_ray ray, t_obj *hit_obj)
{
	t_color	color;

	if (0.0001 < env->t && env->t < 8000.0)
		color = lighting(env->obj, &hit_obj, ray, env->t);
	else
		color = (t_color){0, 0, 0};
	if (NULL != hit_obj)
		hit_obj->current = 0;
	sum_color(sum, &color, env->p, ADD);
}

static t_color	get_pixel_color(t_env *env, t_list *list, int x, int y)
{
//	double	sub[2];
	t_ray	ray;
	t_obj	*hit_obj;
	double	sum[3];
	t_color	color;

//	sub[1] = y;
	sum_color(sum, &color, env->p, INIT);
	env->p = 0.0;
//	while (sub[1] < y + 1)
//	{
//		sub[0] = x;
//		while (sub[0] < x + 1)
//		{
			hit_obj = NULL;
			current_ray(x, y, env, &ray);
			env->t = find_closest_t(list, &ray, &hit_obj);
			check_t(env, sum, ray, hit_obj);
//			sub[0] += 1.0 / env->aa;
			env->p += 1;
//		}
//		sub[1] += 1.0 / env->aa;
//	}
	sum_color(sum, &color, env->p, SUM);
	return (color);
}

static void		drawer(t_list *list, t_env *e)
{
	int		x;
	int		y;
	t_color	color;

	x = -1;
	while (++x < HEIGHT)
	{
		y = -1;
		while (++y < WIDTH)
		{
			color = get_pixel_color(e, list, y, x);
			pixel_put(y, x, color, &e->mlx);
		}
	}
}

void			draw_obj(t_env *e)
{
	drawer(e->obj, e);
	mlx_clear_window(e->mlx.mlx, e->mlx.win);
	mlx_put_image_to_window(e->mlx.mlx, e->mlx.win, e->mlx.img, 0, 0);
	display_cam_info(e);
	if (e->is_obj_selected == 1)
	{
		display_info1(e);
		display_info2(e, e->hit_obj);
	}
	ft_put_info(e);
}
