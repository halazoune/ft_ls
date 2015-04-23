/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recurs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncoden <ncoden@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/16 11:33:34 by ncoden            #+#    #+#             */
/*   Updated: 2014/11/29 17:59:30 by ncoden           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		recurs_process(char *options, char *path, size_t path_size,
				t_list *content)
{
	t_dir		*dirent;
	size_t		newpath_size;

	while (content != NULL)
	{
		dirent = ((t_dir **)content->content)[0];
		OPT_PRINT = (dirent->d_name[0] != '.');
		if (OPT_BR && dirent->d_type == DT_DIR
				&& ft_strcmp(dirent->d_name, ".") != 0
				&& ft_strcmp(dirent->d_name, "..") != 0)
		{
			if (NEED_PATH)
				newpath_size = set_path(path, dirent->d_name, path_size);
			if (dir_process(options, path, newpath_size) == -1)
				error(dirent->d_name);
		}
		content = content->next;
	}
}
