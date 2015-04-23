/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncoden <ncoden@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/16 11:27:50 by ncoden            #+#    #+#             */
/*   Updated: 2014/11/29 18:09:11 by ncoden           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_list		*args_process(char *options, char **argv, int argc)
{
	int			i;
	t_list		*dirlst;
	t_list		*errors;

	dirlst = NULL;
	errors = NULL;
	i = get_options(options, argv, argc);
	if (i == argc)
	{
		if (!(make_content(options, &dirlst, ".")))
			return (NULL);
	}
	while (i < argc)
	{
		if (!(make_content(options, &dirlst, argv[i])))
			if (!(make_error(&errors, argv[i])))
				return (NULL);
		i++;
	}
	if (errors != NULL)
		print_errors(errors);
	return (dirlst);
}

int			get_options(char *options, char **argv, int argc)
{
	int		i;

	i = 1;
	ft_bzero(options, 6);
	OPT_PRINT = 1;
	while (i < argc && argv[i][0] == '-' && argv[i][1] != '\0')
	{
		add_options(options, argv[i]);
		i++;
	}
	return (i);
}

void		add_options(char *options, char *new)
{
	int		i;

	i = 1;
	while (new[i] != '\0')
	{
		if (new[i] == 'l')
			OPT_L = 1;
		else if (new[i] == 'R')
			OPT_BR = 1;
		else if (new[i] == 'a')
			OPT_A = 1;
		else if (new[i] == 'r')
			OPT_R = 1;
		else if (new[i] == 't')
			OPT_T = 1;
		else
		{
			ft_putstr("ls: illegal option -- ");
			ft_putchar(new[i]);
			ft_putstr("\nusage: ls [-Ralrt] [file ...]\n");
			exit(0);
		}
		i++;
	}
}

t_list		*make_content(char *options, t_list **lst, char *name)
{
	void		**datas;
	t_dir		**dirent;
	t_stat		**dstat;

	if (!(datas = (void **)malloc(sizeof(void *) * 2)))
		return (NULL);
	dirent = &(((t_dir **)datas)[0]);
	dstat = &(((t_stat **)datas)[1]);
	if (!(*dirent = (t_dir *)malloc(sizeof(t_dir))))
		return (NULL);
	ft_strcpy((*dirent)->d_name, name);
	(*dirent)->d_type = DT_UNKNOWN;
	if (!(*dstat = get_stat(options, name, *dirent)))
		return (NULL);
	return (add_content(options, lst, datas));
}

t_list		*make_error(t_list **errors, char *name)
{
	t_err	*err;

	if (!(err = ft_errnew(errno, name)))
		return (NULL);
	return (ft_lstlnby(errors, err, sizeof(t_err), sort_error));
}
