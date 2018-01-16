/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abassibe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/13 05:18:30 by abassibe          #+#    #+#             */
/*   Updated: 2018/01/16 04:11:36 by abassibe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

char	*creat_bin(char *str)
{
	char	**tab;
	char	*tmp;

	tab = ft_strsplit(str, '.');
	tmp = ft_strjoin(tab[0], ".cor");
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
