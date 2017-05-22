/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_to_cam.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thou <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/19 18:20:58 by thou              #+#    #+#             */
/*   Updated: 2017/05/22 15:49:31 by thou             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int				check_param(const char *str, int i, int max)
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

t_vector		input_vector(const char *tab, int *i, double w)
{
	t_vector	vec;

	vec.x = ft_atof(tab, &(*i));
	vec.y = ft_atof(tab, &(*i));
	vec.z = ft_atof(tab, &(*i));
	vec.w = w;
	return (vec);
}

int				parser_cam(t_cam *cam, const char **tab)
{
	int	i;

	if (ft_strcmp("camera", tab[0]) || ft_strcmp("{", tab[1]) ||
			ft_strncmp("\tpos(", tab[2], 5) || !(check_param(tab[2], 5, 3)))
		return (0);
	i = 5;
	cam->pos = input_vector(tab[2], &i, 1.0);
	if (ft_strcmp(")", &tab[2][i]) || ft_strncmp("\tdir(", tab[3], 5) ||
			!(check_param(tab[2], 5, 3)))
		return (0);
	i = 5;
	cam->dir = input_vector(tab[3], &i, 1.0);
	cam->lookat = cam->dir;
	if (0 != ft_strcmp(")", &tab[3][i]) || 0 != ft_strcmp("}", tab[4]))
		return (0);
	return (1);
}
