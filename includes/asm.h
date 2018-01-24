/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abassibe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/12 02:46:44 by abassibe          #+#    #+#             */
/*   Updated: 2018/01/24 05:57:07 by abassibe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H

# include "libft.h"
# include "op.h"
# include <fcntl.h>

# define FD env->fd_bin

extern t_op				op_tab[17];

typedef struct			s_label
{
	char				*label_name;
	int					pos;
	struct s_label		*next;
}						t_label;

typedef struct			s_ulabel
{
	char				*label;
	struct s_ulabel		*next;
}						t_ulabel;

typedef struct			s_env
{
	char				*file_name;
	int					fd_bin;
	int					fd;
	int					champ_size;
	char				*bin_name;
	t_label				*label;
	t_ulabel			*ulab;
	char				name;
	char				comment;
	char				*save[3];
	char				**op;
}						t_env;

char					parseur(t_env *env, const char *file_name);
char					pars_name_comment(t_env *env, const char *str);
char					pars_core(t_env *env, const char *str);
char					label_verif(t_env *env);
char					comment_or_empty(const char *str);
void					kingdom_hearts(t_env *env);
char					*creat_bin(char *str);
void					alloc_operators(t_env *env);
char					save_ulabel(t_env *env, const char *str);
char					get_op1(t_env *env, const char *str);
char					is_dir(t_env *env, const char *str);
char					get_op6(t_env *env, const char *str, char **tab);
char					get_op11(t_env *env, const char *str, char **tab);
char					check_ld(t_env *env, char **tab);
char					check_st(t_env *env, char **tab);
char					check_add(t_env *env, char **tab);
char					check_and(t_env *env, char **tab);
char					check_ldi(t_env *env, char **tab);
char					check_sti(t_env *env, char **tab);
char					is_reg(const char *str);
char					is_ind(t_env *env, const char *str);
char					nl_end_of_file(int fd);
void					free_tab(char **str, char **tab, int i);
void					free_operator(t_env *env);
void					free_struct(t_env *env);
void					ft_error(const char *str, const int check);

#endif
