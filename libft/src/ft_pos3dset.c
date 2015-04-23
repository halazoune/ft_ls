/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pos3dset.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncoden <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/29 15:06:52 by ncoden            #+#    #+#             */
/*   Updated: 2014/11/29 16:09:05 by ncoden           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_pos3dset(t_pos3d *pos3d, int x, int y, int z)
{
	if (pos3d)
	{
		pos3d->x = x;
		pos3d->y = y;
		pos3d->z = z;
	}
}