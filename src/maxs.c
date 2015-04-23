/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maxs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncoden <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/24 18:00:56 by ncoden            #+#    #+#             */
/*   Updated: 2014/11/29 18:00:13 by ncoden           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		get_maxs(t_list *content, char *buff)
{
	int			lnk;
	uid_t		uid;
	gid_t		gid;
	t_stat		*stat;

	lnk = 0;
	uid = 0;
	gid = 0;
	ft_bzero(buff, 5);
	while (content != NULL)
	{
		stat = ((t_stat **)content->content)[1];
		lnk = (stat->st_nlink > lnk) ? stat->st_nlink : lnk;
		get_maxs_uid_gid(buff, stat, &uid, &gid);
		get_maxs_size(buff, ((t_dir **)content->content)[0], stat);
		content = content->next;
	}
	buff[0] = (char)ft_nbrlen(lnk);
}

void		get_maxs_uid_gid(char *buff, t_stat *stat, uid_t *uid, gid_t *gid)
{
	int				size;
	struct passwd	*usr;
	struct group	*grp;

	usr = NULL;
	if (stat->st_uid != *uid)
	{
		usr = getpwuid(stat->st_uid);
		if (usr != NULL && (size = ft_strlen(usr->pw_name)) && size > buff[1])
		{
			buff[1] = size;
			*uid = stat->st_uid;
		}
	}
	if (usr == NULL && buff[1] < 4)
		buff[1] = 4;
	if (stat->st_gid != *gid)
	{
		grp = getgrgid(stat->st_gid);
		if (grp != NULL && (size = ft_strlen(grp->gr_name)) && size > buff[2])
		{
			buff[2] = size;
			*gid = stat->st_gid;
		}
	}
}

void		get_maxs_size(char *buff, t_dir *dirent, t_stat *stat)
{
	int		len;

	if ((len = ft_nbrlen(stat->st_size)) > buff[3])
		buff[3] = len;
	if (dirent->d_type == DT_CHR || dirent->d_type == DT_BLK)
	{
		if ((len = ft_nbrlen(MINOR(stat->st_rdev))) > buff[4])
			buff[4] = len;
		if ((len = ft_nbrlen(MAJOR(stat->st_rdev)) + 2 + buff[4] + 1) > buff[3])
			buff[3] = len;
	}
}
