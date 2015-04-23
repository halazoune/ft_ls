/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_rights.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncoden <ncoden@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/18 15:27:21 by ncoden            #+#    #+#             */
/*   Updated: 2014/11/29 17:59:01 by ncoden           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		print_type(unsigned char type)
{
	if (type == DT_UNKNOWN || type == DT_REG)
		ft_putchar('-');
	else if (type == DT_DIR)
		ft_putchar('d');
	else if (type == DT_FIFO)
		ft_putchar('p');
	else if (type == DT_SOCK)
		ft_putchar('s');
	else if (type == DT_CHR)
		ft_putchar('c');
	else if (type == DT_BLK)
		ft_putchar('b');
	else if (type == DT_LNK)
		ft_putchar('l');
	else
		ft_putchar('-');
}

void		print_rights(int rights, int level)
{
	int		nbr;
	int		mode;

	if (level < 3)
	{
		print_rights(rights / 8, level + 1);
		mode = rights / ft_power(8, 3 - level);
		nbr = rights % 8;
		ft_putchar((nbr >= 4) ? 'r' : '-');
		ft_putchar((nbr % 4 >= 2) ? 'w' : '-');
		if ((level == 2 && mode == 4) || (level == 1 && mode == 2))
			ft_putchar((nbr % 2) ? 's' : 'S');
		else if (level == 0 && mode == 1)
			ft_putchar((nbr % 2) ? 't' : 'T');
		else
			ft_putchar((nbr % 2) ? 'x' : '-');
	}
}

void		print_xrights(char *fpath)
{
	int		xattrs;
	acl_t	acl;

	xattrs = (int)listxattr(fpath, NULL, 1, XATTR_NOFOLLOW);
	if (xattrs > 0)
		ft_putchar('@');
	else
	{
		acl = acl_get_file(fpath, ACL_TYPE_EXTENDED);
		if (acl != NULL)
			ft_putchar('+');
		else
			ft_putchar(' ');
	}
}

void		print_links(int nbr, char *maxs)
{
	ft_putchar(' ');
	if (maxs != NULL)
		ft_putnbrright(nbr, maxs[0]);
	else
		ft_putnbr(nbr);
	ft_putchar(' ');
}
