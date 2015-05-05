/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dirs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncoden <ncoden@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/14 16:07:36 by ncoden            #+#    #+#             */
/*   Updated: 2015/05/05 12:03:10 by ncoden           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int			dir_process(char *options, char *path, size_t path_size)
{
	DIR				*dir;
	t_list			*content;

	if (OPT_PRINT)
		print_dirname(options, path);
	dir = opendir(path);
	if (dir == NULL)
		return (-1);
	content = get_content(options, path, path_size, dir);
	if (content != NULL)
	{
		if (NEED_PATH)
			path[path_size] = '\0';
		if (OPT_PRINT)
			print_process(options, path, path_size, content);
		recurs_process(options, path, path_size, content);
		ft_lstdel(&content, free_datas);
	}
	closedir(dir);
	return (0);
}

t_list		*get_content(char *options, char *path, size_t path_size, DIR *dir)
{
	t_list		*lst;
	void		**datas;
	t_dir		*dirent;

	lst = NULL;
	while ((dirent = readdir(dir)))
	{
		if (dirent->d_name[0] != '.' || OPT_A || (OPT_BR
				&& dirent->d_type == DT_DIR
				&& ft_strcmp(dirent->d_name, ".") != 0
				&& ft_strcmp(dirent->d_name, "..") != 0))
		{
			if (NEED_PATH)
				set_path(path, dirent->d_name, path_size);
			if (!(datas = get_content_datas(options, path, dirent)))
				error(dirent->d_name);
			else
				add_content(options, &lst, datas);
		}
	}
	return (lst);
}

void		**get_content_datas(char *options, char *fpath, t_dir *dirent)
{
	void		**datas;

	if (!(datas = (void **)malloc(sizeof(void *) * 2)))
		return (NULL);
	if (!(datas[0] = (t_dir *)ft_memdup(dirent, sizeof(t_dir))))
		return (NULL);
	datas[1] = NULL;
	if (OPT_L || OPT_T || (dirent->d_type == DT_UNKNOWN))
	{
		if (!(datas[1] = get_stat(options, fpath, ((t_dir **)datas)[0])))
			return (NULL);
	}
	return (datas);
}

t_stat		*get_stat(char *options, char *fpath, t_dir *dirent)
{
	t_stat *dstat;

	(void)options;
	if (!(dstat = (t_stat *)malloc(sizeof(t_stat))))
		return (NULL);
	if (dirent->d_type == DT_LNK || dirent->d_type == DT_UNKNOWN)
	{
		if (lstat(fpath, dstat) == -1)
			return (NULL);
	}
	else if (stat(fpath, dstat) == -1)
		return (NULL);
	if (dirent->d_type == DT_UNKNOWN)
		dirent->d_type = IFTODT(dstat->st_mode);
	return (dstat);
}

t_list		*add_content(char *options, t_list **lst, void **datas)
{
	int		(*f)(const void *, const void *, size_t, size_t);

	f = (OPT_T) ? &sort_time : &sort_alpha;
	if (!OPT_R)
		return (ft_lstlnby(lst, datas, sizeof(void *) * 2, f));
	else
		return (ft_lstlnrby(lst, datas, sizeof(void *) * 2, f));
}
