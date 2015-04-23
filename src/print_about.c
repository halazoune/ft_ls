/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_about.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncoden <ncoden@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/18 15:27:16 by ncoden            #+#    #+#             */
/*   Updated: 2014/11/29 17:59:55 by ncoden           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		print_groups(t_stat *stat, char *maxs)
{
	struct passwd	*usr;
	struct group	*grp;

	usr = getpwuid(stat->st_uid);
	if (usr != NULL)
		ft_putstrleft(usr->pw_name, (maxs) ? maxs[1] : 0);
	else
		ft_putnbrleft(stat->st_uid, (maxs) ? maxs[1] : 0);
	ft_putspace(2);
	grp = getgrgid(stat->st_gid);
	if (grp != NULL)
		ft_putstrleft(grp->gr_name, (maxs) ? maxs[2] : 0);
	ft_putspace(2);
}

void		print_device(int device, char *maxs)
{
	if (maxs != NULL)
		ft_putnbrright(MAJOR(device), maxs[3] - 2 - maxs[4]);
	else
		ft_putnbr(MAJOR(device));
	ft_putstr(", ");
	ft_putnbrright(MINOR(device), (maxs) ? maxs[4] : 0);
}

void		print_size(int size, char *maxs)
{
	if (maxs != NULL)
		ft_putnbrright(size, maxs[3]);
	else
		ft_putnbr(size);
}

void		print_about(t_stat *stat)
{
	time_t		now;
	time_t		mtime;
	time_t		diff;
	char		*mtime_str;

	now = time(NULL);
	mtime = stat->st_mtime;
	mtime_str = ctime(&mtime);
	diff = now - mtime;
	ft_putchar(' ');
	ft_putnstr(&(mtime_str[4]), 6);
	ft_putchar(' ');
	if (diff < (-3600 * 24 * 30.5 * 6) || diff > (3600 * 24 * 30.5 * 6))
	{
		ft_putchar(' ');
		ft_putnstr(&(mtime_str[20]), 4);
	}
	else
		ft_putnstr(&(mtime_str[11]), 5);
	ft_putchar(' ');
	mtime_str = mtime_str;
}

void		print_lnkabout(char *fpath)
{
	int		path_size;
	char	*path_save;

	if (!(path_save = ft_strdup(fpath)))
		return ;
	path_size = readlink(fpath, fpath, 1024);
	if (path_size > 0)
	{
		fpath[path_size] = '\0';
		ft_putstr(" -> ");
		ft_putstr(fpath);
	}
	ft_strcpy(fpath, path_save);
	free(path_save);
}
