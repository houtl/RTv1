/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_scene.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thou <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/19 18:21:58 by thou              #+#    #+#             */
/*   Updated: 2017/05/22 16:26:29 by thou             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int			check_param(const char *str, int i, int max)
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

t_vector	input_vector(const char *tab, int *i, double w)
{
	t_vector	vec;

	vec.x = ft_atof(tab, &(*i));
	vec.y = ft_atof(tab, &(*i));
	vec.z = ft_atof(tab, &(*i));
	vec.w = w;
	return (vec);
}

static int	parser_cam(t_cam *cam, const char **tab)
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

static char	**file_to_tab(char *file)
{
	char	**tab;
	int		fd;
	int		i;
	char	*line;

	i = 0;
	SAFEMALL((fd = open(file, O_RDONLY)));
	while (get_next_line(fd, &line) > 0)
	{
		i++;
		free(line);
	}
	close(fd) == -1 ? err_exit("Unable to close file") : 0;
	SAFEMALL((fd = open(file, O_RDONLY)));
	SAFEMALL((tab = (char **)malloc(sizeof(char *) * (i + 1))));
	i = 0;
	while (get_next_line(fd, &line) > 0)
		tab[i++] = line;
	tab[i] = NULL;
	close(fd) == -1 ? err_exit("Unable to close file") : 0;
	return (tab);
}

int			get_scene(t_list **obj, t_cam *cam, char *file)
{
	char	**tab;
	int		i;

	if (!(tab = file_to_tab(file)))
		return (0);
	if (0 == parser_cam(cam, (const char**)tab))
		return (0);
	if (0 == parser_obj(obj, (const char**)tab, 5))
		return (0);
	i = 0;
	while (tab[i] != NULL)
		free(tab[i++]);
	free(tab);
	return (1);
}
