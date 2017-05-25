/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thou <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/19 18:21:29 by thou              #+#    #+#             */
/*   Updated: 2017/05/25 17:43:21 by thou             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int	get_colpos(t_obj *obj, const char **tab, int *i)
{
	int		j;
	double	check;

	if (ft_strncmp("\t\tcol(", tab[*i], 6))
		return (0);
	j = 6;
	if (0 > (check = ft_atof(tab[*i], &j)) || check > 255)
		return (0);
	obj->color.r = (uint8_t)check;
	if (0 > (check = ft_atof(tab[*i], &j)) || check > 255)
		return (0);
	obj->color.g = (uint8_t)check;
	if (0 > (check = ft_atof(tab[*i], &j)) || check > 255)
		return (0);
	obj->color.b = (uint8_t)check;
	if (')' != tab[*i][j] || '\0' != tab[*i][j + 1] ||
			ft_strncmp("\t\tpos(", tab[++(*i)], 6))
		return (0);
	j = 6;
	SAFEMALL0((input_vector(tab[*i], &j, 1.0, &obj->pos)));
	++(*i);
	return (1);
}

int	get_size(t_obj *obj, const char **tab, int *i)
{
	int	j;

	if (ft_strncmp("\t\tsize(", tab[*i], 7))
		return (0);
	j = 7;
	obj->size = ft_atof(tab[*i], &j);
	while (ft_isdigit(tab[*i][j]))
		++j;
	if (')' != tab[*i][j] || '\0' != tab[*i][j + 1])
		return (0);
	++(*i);
	return (1);
}

int	get_rot(t_obj *obj, const char **tab, int *i)
{
	int	j;

	if (ft_strncmp("\t\trot(", tab[*i], 6))
		return (0);
	j = 6;
	SAFEMALL0((input_vector(tab[*i], &j, 0.0, &obj->rot)));
	++(*i);
	return (1);
}
