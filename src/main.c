/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncoden <ncoden@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/14 10:37:29 by ncoden            #+#    #+#             */
/*   Updated: 2015/05/05 12:02:32 by ncoden           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int			main(int argc, char **argv)
{
	t_list	*dirlst;
	char	options[6];
	char	*path;

	if (!(dirlst = args_process(options, argv, argc)))
		return (0);
	path = NULL;
	if (NEED_PATH)
		if (!(path = (char *)malloc(sizeof(char) * 1024)))
			return (0);
	ls(options, dirlst, path);
	return (0);
}

void		ls(char *options, t_list *lst, char *path)
{
	size_t		path_size;

	OPT_PRINT = (lst->next == NULL) ? 3 : 2;
	while (lst != NULL)
	{
		if (((t_dir **)lst->content)[0]->d_type == DT_DIR)
		{
			path = ((t_dir **)lst->content)[0]->d_name;
			if (NEED_PATH)
				path_size = ft_stricpy(path,
					((t_dir **)lst->content)[0]->d_name);
			if (dir_process(options, path, path_size) == -1)
				error(((t_dir **)lst->content)[0]->d_name);
		}
		else
			print_content(options, lst->content, path, NULL);
		lst = lst->next;
		OPT_PRINT = 1;
	}
}
