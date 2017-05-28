/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_scene.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thou <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/19 18:21:58 by thou              #+#    #+#             */
/*   Updated: 2017/05/28 15:14:25 by thou             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int			input_vector(const char *str, int *i, t_vector *vec)
{
	int		words;

	words = 0;
	while (str[*i] != '\0' && str[*i] != ')')
	{
		while (ft_iswhitespace(str[*i]) == 1)
			++(*i);
		if (ft_iswhitespace(str[*i]) == 0 && str[*i] != 0 && str[*i] != ')')
			++words;
		words == 1 ? vec->x = ft_atoi(&str[*i]) : 0;
		words == 2 ? vec->y = ft_atoi(&str[*i]) : 0;
		words == 3 ? vec->z = ft_atoi(&str[*i]) : 0;
		while (ft_iswhitespace(str[*i]) == 0 && str[*i] != 0 && str[*i] != ')')
			++(*i);
	}
	if (str[*i] != ')' || str[*i + 1] != 0)
		return (0);
	return (words == 3 ? 1 : 0);
}

static int	parser_cam(t_env *e, const char **tab)
{
	int		i;

	if (ft_strcmp("camera", tab[0]) || ft_strcmp("{", tab[1]) ||
			ft_strncmp("\tpos(", tab[2], 5))
		return (0);
	i = 5;
	SAFEMALL0((input_vector(tab[2], &i, &e->cam.pos)));
	if (ft_strcmp(")", &tab[2][i]) || ft_strncmp("\tdir(", tab[3], 5))
		return (0);
	i = 5;
	SAFEMALL0((input_vector(tab[3], &i, &e->cam.dir)));
	e->cam.lookat = e->cam.dir;
	if (0 != ft_strcmp("}", tab[4]))
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

int			get_scene(t_env *e, char *file)
{
	char	**tab;
	int		i;

	if (!(tab = file_to_tab(file)))
		return (0);
	if (0 == parser_cam(e, (const char**)tab))
		return (0);
	if (0 == parser_obj(&e->obj, (const char**)tab, 5))
		return (0);
	i = 0;
	while (tab[i] != NULL)
		free(tab[i++]);
	free(tab);
	return (1);
}
