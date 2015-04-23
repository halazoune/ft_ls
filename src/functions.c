/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncoden <ncoden@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/18 09:20:04 by ncoden            #+#    #+#             */
/*   Updated: 2014/11/29 18:04:28 by ncoden           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		error(char *str)
{
	ft_putstr("ls: ");
	perror(str);
}

void		print_errors(t_list *errors)
{
	t_list	*next;

	while (errors != NULL)
	{
		ft_putstr("ls: ");
		ft_putstr(((t_err *)errors->content)->mess);
		ft_putstr(": ");
		ft_putendl(strerror(((t_err *)errors->content)->err));
		next = errors->next;
		free(((t_err *)errors->content)->mess);
		free((t_err *)errors->content);
		free(errors);
		errors = next;
	}
}

size_t		set_path(char *path, const char *src, size_t path_size)
{
	size_t		upath_size;

	if (path[0] == '/' && path_size == 1)
		path_size--;
	path[path_size] = '/';
	upath_size = ft_stricpy(&(path[path_size + 1]), src);
	return (path_size + 1 + upath_size);
}

void		free_datas(void *content, size_t content_size)
{
	void	**datas;

	content_size = content_size;
	datas = content;
	if (datas != NULL)
	{
		if ((t_dir **)datas[0] != NULL)
			free(((t_dir **)datas)[0]);
		if ((t_stat **)datas[1] != NULL)
			free(((t_stat **)datas)[1]);
		free(datas);
	}
}
