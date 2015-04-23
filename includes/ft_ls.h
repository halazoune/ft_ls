/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncoden <ncoden@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/14 10:35:10 by ncoden            #+#    #+#             */
/*   Updated: 2014/11/29 18:03:21 by ncoden           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include <dirent.h>
# include <stdio.h>
# include <pwd.h>
# include <grp.h>
# include <time.h>
# include <sys/errno.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/xattr.h>
# include <sys/acl.h>
# include <uuid/uuid.h>
# include "libft.h"

# define OPT_PRINT (options[0])
# define OPT_L (options[1])
# define OPT_BR (options[2])
# define OPT_A (options[3])
# define OPT_R (options[4])
# define OPT_T (options[5])
# define NEED_PATH (OPT_L || OPT_BR || OPT_T)

# define MINOR(x) ((x) & 0xffffff)
# define MAJOR(x) (((x) >> 24) & 0xff)

typedef struct dirent	t_dir;
typedef struct stat		t_stat;
typedef struct timespec	t_time;

void		ls(char *options, t_list *lst, char *path);

t_list		*args_process(char *options, char **argv, int argc);
int			get_options(char *options, char **argv, int argc);
void		add_options(char *options, char *new);
t_list		*make_content(char *options, t_list **lst, char *name);
t_list		*make_error(t_list **errors, char *name);

int			dir_process(char *options, char *path, size_t path_size);
t_list		*get_content(char *options, char *path, size_t path_size, DIR *dir);
void		**get_content_datas(char *options, char *fpath, t_dir *dirent);
t_stat		*get_stat(char *optios, char *fpath, t_dir *dirent);
t_list		*add_content(char *options, t_list **lst, void **datas);
int			filter_content(char *options, void **cont1, void **cont2);

int			sort_alpha(const void *c1, const void *c2, size_t csize1,
				size_t csize2);
int			sort_time(const void *c1, const void *c2, size_t csize1,
				size_t csize2);
int			sort_error(const void *c1, const void *c2, size_t csize1,
				size_t csize2);

void		recurs_process(char *options, char *path, size_t path_size,
				t_list *content);

void		print_process(char *options, char *path, size_t path_size,
				t_list *content);
void		print_dirname(char *options, char *dirpath);
void		print_dirtotal(t_list *content);

void		print_content(char *options, void **datas, char *fpath, char *maxs);
void		print_type(unsigned char type);
void		print_rights(int rights, int level);
void		print_xrights(char *fpath);
void		print_links(int nbr, char *maxs);
void		print_groups(t_stat *stat, char *maxs);
void		print_device(int device, char *maxs);
void		print_size(int size, char *maxs);
void		print_about(t_stat *stat);
void		print_lnkabout(char *fpath);

void		get_maxs(t_list *content, char *buff);
void		get_maxs_uid_gid(char *buff, t_stat *stat, uid_t *uid, gid_t *gid);
void		get_maxs_size(char *buff, t_dir *dirent, t_stat *stat);

void		error(char *str);
void		print_errors(t_list *errors);
void		free_datas(void *content, size_t content_size);
size_t		set_path(char *path, const char *src, size_t path_size);

#endif
