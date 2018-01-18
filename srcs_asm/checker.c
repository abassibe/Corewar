/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abassibe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/18 05:29:09 by abassibe          #+#    #+#             */
/*   Updated: 2018/01/18 05:31:03 by abassibe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

char	check_st(t_env *env, char **tab)
{
	if (is_reg(tab[0]))
		if (is_ind(env, tab[1]) || is_reg(tab[1]))
			return (1);
	return (0);
}

char	check_add(char **tab)
{
	if (is_reg(tab[0]))
		if (is_reg(tab[1]))
			if (is_reg(tab[2]))
				return (1);
	return (0);
}

char	check_and(t_env *env, char **tab)
{
	if (is_dir(env, tab[0]) || is_ind(env, tab[0]) || is_reg(tab[0]))
		if (is_dir(env, tab[1]) || is_ind(env, tab[1]) || is_reg(tab[1]))
			if (is_reg(tab[2]))
				return (1);
	return (0);
}

char	check_ldi(t_env *env, char **tab)
{
	if (is_dir(env, tab[0]) || is_ind(env, tab[0]) || is_reg(tab[0]))
		if (is_dir(env, tab[1]) || is_reg(tab[1]))
			if (is_reg(tab[2]))
				return (1);
	return (0);
}

char	check_sti(t_env *env, char **tab)
{
	if (is_reg(tab[0]))
		if (is_dir(env, tab[1]) || is_ind(env, tab[1]) || is_reg(tab[1]))
			if (is_dir(env, tab[2]) || is_reg(tab[2]))
				return (1);
	return (0);
}
