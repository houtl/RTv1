/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thou <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/19 18:20:45 by thou              #+#    #+#             */
/*   Updated: 2017/05/19 18:20:48 by thou             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_color	get_color(int color)
{
	t_color	col;

	col.r = (color & 0xFF0000) >> 16;
	col.g = (color & 0xFF00) >> 8;
	col.b = (color & 0xFF);
	return (col);
}

t_color	ft_color(t_obj *hit_obj)
{
	t_color	col;

	col.r = (uint8_t)hit_obj->color.r;
	col.g = (uint8_t)hit_obj->color.g;
	col.g = (uint8_t)hit_obj->color.b;
	return (col);
}

void	pixel_put(int x, int y, t_color col, t_mlx *mlx)
{
	int	index;

	if (x >= 0 && y >= 0 && x < WIDTH && y < HEIGHT)
	{
		index = y * mlx->size_line + (x * (mlx->bpp / 8));
		mlx->data[index] = *((char*)&col.b);
		mlx->data[++index] = *((char*)&col.g);
		mlx->data[++index] = *((char*)&col.r);
	}
}
