/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abassibe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/13 05:18:30 by abassibe          #+#    #+#             */
/*   Updated: 2018/01/25 03:11:08 by abassibe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

char	*creat_bin(char *str)
{
	char	**tab;
	char	*tmp;

	tab = ft_strsplit(str, '.');
//	tmp = ft_strjoin(tab[0], ".cor");
	tmp = ft_strjoin("test", ".cor");
	free(tab[0]);
	free(tab[1]);
	free(tab);
	return (tmp);
}

void	alloc_operators(t_env *env)
{
	env->op = ft_memalloc(sizeof(char *) * 16);
	env->op[0] = ft_strdup("live");
	env->op[1] = ft_strdup("ld");
	env->op[2] = ft_strdup("st");
	env->op[3] = ft_strdup("add");
	env->op[4] = ft_strdup("sub");
	env->op[5] = ft_strdup("and");
	env->op[6] = ft_strdup("or");
	env->op[7] = ft_strdup("xor");
	env->op[8] = ft_strdup("zjmp");
	env->op[9] = ft_strdup("ldi");
	env->op[10] = ft_strdup("sti");
	env->op[11] = ft_strdup("fork");
	env->op[12] = ft_strdup("lld");
	env->op[13] = ft_strdup("lldi");
	env->op[14] = ft_strdup("lfork");
	env->op[15] = ft_strdup("aff");
}

void	alloc_op_functions(t_env *env)
{
	env->opf = ft_memalloc(sizeof(void *) * 16);
	env->opf[0] = print_live;
	env->opf[1] = print_ld;
	env->opf[2] = print_live;
	env->opf[3] = print_live;
	env->opf[4] = print_live;
	env->opf[5] = print_live;
	env->opf[6] = print_live;
	env->opf[7] = print_live;
	env->opf[8] = print_live;
	env->opf[9] = print_live;
	env->opf[10] = print_live;
	env->opf[11] = print_live;
	env->opf[12] = print_live;
	env->opf[13] = print_live;
	env->opf[14] = print_live;
	env->opf[15] = print_live;
/*	env->opf[1] = print_ld;
	env->opf[2] = print_st;
	env->opf[3] = print_add;
	env->opf[4] = print_sub;
	env->opf[5] = print_and;
	env->opf[6] = print_or;
	env->opf[7] = print_xor;
	env->opf[8] = print_zjmp;
	env->opf[9] = print_ldi;
	env->opf[10] = print_sti;
	env->opf[11] = print_fork;
	env->opf[12] = print_lld;
	env->opf[13] = print_lldi;
	env->opf[14] = print_lfork;
	env->opf[15] = print_aff;*/
}

void	free_tab(char **str, char **tab, int i)
{
	int		j;

	j = -1;
	while (++j < i)
		ft_strdel(&str[j]);
	free(tab);
}

void	free_operator(t_env *env)
{
	int		i;

	i = -1;
	while (++i < 16)
		ft_strdel(&env->op[i]);
	free(env->op);
}

void	free_struct(t_env *env)
{
	t_label		*tmp;
	t_ulabel	*tmp2;

	while (env->label)
	{
		tmp = env->label->next;
		ft_strdel(&env->label->label_name);
		free(env->label);
		env->label = tmp;
	}
	while (env->ulab)
	{
		tmp2 = env->ulab->next;
		ft_strdel(&env->ulab->label);
		free(env->ulab);
		env->ulab = tmp2;
	}
	ft_strdel(&env->file_name);
}
