/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncoden <ncoden@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/16 11:14:39 by ncoden            #+#    #+#             */
/*   Updated: 2014/11/29 17:59:12 by ncoden           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		print_process(char *options, char *path, size_t path_size,
				t_list *content)
{
	char		maxs[5];
	t_dir		*dirent;

	if (OPT_L)
	{
		get_maxs(content, maxs);
		print_dirtotal(content);
	}
	while (content != NULL)
	{
		dirent = ((t_dir **)content->content)[0];
		if (OPT_A || dirent->d_name[0] != '.')
		{
			if (NEED_PATH)
				set_path(path, dirent->d_name, path_size);
			print_content(options, content->content, path, maxs);
		}
		content = content->next;
	}
}

void		print_dirname(char *options, char *dirpath)
{
	if (OPT_PRINT)
	{
		if (OPT_PRINT < 2)
			ft_putchar('\n');
		if (OPT_PRINT < 3)
		{
			ft_putstr(dirpath);
			ft_putstr(":\n");
		}
	}
}

void		print_dirtotal(t_list *content)
{
	int		total;

	total = 0;
	while (content != NULL)
	{
		total += (int)((t_stat **)content->content)[1]->st_blocks;
		content = content->next;
	}
	if (total > 0)
	{
		ft_putstr("total ");
		ft_putnbr(total);
		ft_putchar('\n');
	}
}

void		print_content(char *options, void **datas, char *fpath, char *maxs)
{
	t_dir		*dirent;
	t_stat		*stat;

	dirent = ((t_dir **)datas)[0];
	stat = ((t_stat **)datas)[1];
	if (OPT_L)
	{
		print_type(dirent->d_type);
		print_rights((int)stat->st_mode % (8 * 8 * 8 * 8), 0);
		print_xrights(fpath);
		print_links(stat->st_nlink, maxs);
		print_groups(stat, maxs);
		if (dirent->d_type == DT_CHR || dirent->d_type == DT_BLK)
			print_device(stat->st_rdev, maxs);
		else
			print_size(stat->st_size, maxs);
		print_about(stat);
	}
	ft_putstr(dirent->d_name);
	if (OPT_L && dirent->d_type == DT_LNK)
		print_lnkabout(fpath);
	ft_putchar('\n');
}
