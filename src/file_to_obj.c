/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_to_obj.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thou <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/19 18:21:09 by thou              #+#    #+#             */
/*   Updated: 2017/05/22 16:09:04 by thou             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int			type_object(const char *str)
{
	if (!(ft_strcmp("\tlight", str)))
		return (LIGHT);
	if (!(ft_strcmp("\tplane", str)))
		return (PLANE);
	if (!(ft_strcmp("\tcylinder", str)))
		return (CYLINDER);
	if (!(ft_strcmp("\tcone", str)))
		return (CONE);
	if (!(ft_strcmp("\tsphere", str)))
		return (SPHERE);
	return (0);
}

static int	get_obj(t_list **obj, const char **tab, int *i)
{
	t_obj	*new;
	t_list	*lstnew;

	SAFEMALLOC((type_object(tab[*i])));
	SAFEMALL0((new = (t_obj *)malloc(sizeof(t_obj))));
	new->name = type_object(tab[(*i)++]);
	if (ft_strcmp("\t{", tab[(*i)++]) || !(get_colpos(new, tab, i)))
		return (0);
	if (new->name != LIGHT)
	{
		if (new->name != PLANE && 0 == get_size(new, tab, i))
			return (0);
		if (new->name != SPHERE && 0 == get_rot(new, tab, i))
			return (0);
		if (0 == get_light_info(new, tab, i))
			return (0);
	}
	if (ft_strcmp("\t}", tab[*(i++)]))
		return (0);
	new->current = 0;
	SAFEMALL0((lstnew = ft_lstnew(NULL, 0)));
	lstnew->content = new;
	ft_lstadd(obj, lstnew);
	return (1);
}

int			parser_obj(t_list **obj, const char **tab, int i)
{
	while (tab[i] && !(ft_strcmp("", tab[i])))
		++i;
	if (!(tab[i]) || ft_strcmp("content", tab[i++]) || ft_strcmp("{", tab[i++]))
		return (0);
	while (tab[i] != NULL)
	{
		if (0 == get_obj(obj, tab, &i))
			return (0);
		else
			++i;
	}
	return (1);
}
