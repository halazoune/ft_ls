/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncoden <ncoden@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/21 12:13:36 by ncoden            #+#    #+#             */
/*   Updated: 2014/11/29 17:56:50 by ncoden           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		sort_alpha(const void *c1, const void *c2, size_t csize1,
			size_t csize2)
{
	int		result;

	csize1 = csize2;
	csize2 = csize1;
	result = (ft_strcmp(((t_dir **)c1)[0]->d_name,
				((t_dir **)c2)[0]->d_name) < 0);
	return (result);
}

int		sort_time(const void *c1, const void *c2, size_t csize1,
			size_t csize2)
{
	int		result;

	csize1 = csize2;
	csize2 = csize1;
	result = ((t_stat **)c1)[1]->st_ctime > ((t_stat **)c2)[1]->st_ctime;
	if (result != 0)
		return (result);
	return (sort_alpha(c1, c2, csize1, csize2));
}

int		sort_error(const void *c1, const void *c2, size_t csize1,
			size_t csize2)
{
	int		result;

	csize1 = csize2;
	csize2 = csize1;
	result = (ft_strcmp(((t_err *)c1)->mess, ((t_err *)c2)->mess) < 0);
	return (result);
}
