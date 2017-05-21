/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_scene.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thou <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/19 18:21:58 by thou              #+#    #+#             */
/*   Updated: 2017/05/21 16:33:50 by thou             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

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
	if (0 == parser_cam(cam, tab))
		return (0);
	if (0 == parser_obj(obj, tab, 5))
		return (0);
	i = 0;
	while (tab[i] != NULL)
		free(tab[i++]);
	free(tab);
	return (1);
}
