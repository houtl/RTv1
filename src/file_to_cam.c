/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_to_cam.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thou <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/19 18:20:58 by thou              #+#    #+#             */
/*   Updated: 2017/05/21 18:20:24 by thou             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int				check_param(char *str, int i, int max)
{
	int	words;

	words = 0;
	while (str[i] != '\0' && str[i] != ')')
	{
		while (ft_iswhitespace(str[i]) == 1)
			i++;
		if (ft_iswhitespace(str[i]) == 0 && str[i] != 0 && str[i] != ')')
			words++;
		while (ft_iswhitespace(str[i]) == 0 && str[i] != 0 && str[i] != ')')
			i++;
	}
	return (words == max ? 1 : 0);
}

static t_vector	input_vector(char *tab, int *i)
{
	t_vector	vec;

	vec.x = ft_atof(tab, &(*i));
	vec.y = ft_atof(tab, &(*i));
	vec.z = ft_atof(tab, &(*i));
	vec.w = 1.0;
	return (vec);
}

int				parser_cam(t_cam *cam, char **tab)
{
	int	i;

	if (0 != ft_strcmp("camera", tab[0]) || 0 != ft_strcmp("{", tab[1]) ||
			0 != ft_strncmp("	pos(", tab[2], 5))
		return (0);
	i = 5;
	if (0 == check_param(tab[2], i, 3))
		return (0);
	cam->pos = input_vector(tab[2], &i);
	if (0 != ft_strcmp(")", &tab[2][i]) ||
			0 != ft_strncmp("	dir(", tab[3], 5))
		return (0);
	i = 5;
	if (0 == check_param(tab[3], i, 3))
		return (0);
	cam->dir = input_vector(tab[3], &i);
	cam->lookat = cam->dir;
	if (0 != ft_strcmp(")", &tab[3][i]) || 0 != ft_strcmp("}", tab[4]))
		return (0);
	return (1);
}
