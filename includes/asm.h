/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abassibe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/12 02:46:44 by abassibe          #+#    #+#             */
/*   Updated: 2018/01/16 05:28:27 by abassibe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "op.h"
#include "fcntl.h"

#define FD env->fd

typedef struct		s_label
{
	char			*label_name;
	int				pos;
	struct s_label	*next;
}					t_label;

typedef struct		s_env
{
	char			*file_name;
	int				fd;
	char			*bin_name;
	t_label			*label;
	char			name;
	char			comment;
	char			**op;
}					t_env;

char				parseur(t_env *env, const char *file_name);
char				pars_name_comment(t_env *env, const char *str);
char				pars_core(t_env *env, const char *str);
char				comment_or_empty(const char *str);
void				kingdom_hearts(t_env *env, const int fd);
char				*creat_bin(char *str);
void				alloc_operators(t_env *env);
void				ft_error(const char *str, const int check);
