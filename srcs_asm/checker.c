/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abassibe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/18 05:29:09 by abassibe          #+#    #+#             */
/*   Updated: 2018/01/25 05:02:37 by abassibe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

char	check_st(t_env *env, char **tab)
{
	if (!tab[0] || ! tab[1])
		return (0);
	while (*tab[0] < 33)
		tab[0]++;
	while (*tab[1] < 33)
		tab[1]++;
	if (is_reg(tab[0]))
	{
		if (is_ind(env, tab[1]))
		{
			env->champ_size += 5;
			return (1);
		}
		else if (is_reg(tab[1]))
		{
			env->champ_size += 4;
			return (1);
		}
	}
	return (0);
}

char	check_add(t_env *env, char **tab)
{
	if (!tab[0] || ! tab[1] || !tab[2])
		return (0);
	while (*tab[0] < 33)
		tab[0]++;
	while (*tab[1] < 33)
		tab[1]++;
	while (*tab[2] < 33)
		tab[2]++;
	if (is_reg(tab[0]))
		if (is_reg(tab[1]))
			if (is_reg(tab[2]))
			{
				env->champ_size += 5;
				return (1);
			}
	return (0);
}

char	check_and(t_env *env, char **tab)
{
	if (!tab[0] || ! tab[1] || !tab[2])
		return (0);
	if (!tab[0] || ! tab[1])
		return (0);
	while (*tab[0] < 33)
		tab[0]++;
	while (*tab[1] < 33)
		tab[1]++;
	while (*tab[2] < 33)
		tab[2]++;
	if (is_dir(env, tab[0]))
	{
		if (is_dir(env, tab[1]))
		{
			if (is_reg(tab[2]))
			{
				env->champ_size += 11;
				return (1);
			}
		}
		else if (is_ind(env, tab[1]))
		{
			if (is_reg(tab[2]))
			{
				env->champ_size += 9;
				return (1);
			}
		}
		else if (is_reg(tab[1]))
			if (is_reg(tab[2]))
			{
				env->champ_size += 8;
				return (1);
			}
	}
	else if (is_ind(env, tab[0]))
	{
		if (is_dir(env, tab[1]))
		{
			if (is_reg(tab[2]))
			{
				env->champ_size += 9;
				return (1);
			}
		}
		else if (is_ind(env, tab[1]))
		{
			if (is_reg(tab[2]))
			{
				env->champ_size += 7;
				return (1);
			}
		}
		else if (is_reg(tab[1]))
			if (is_reg(tab[2]))
			{
				env->champ_size += 6;
				return (1);
			}
	}
	else if (is_reg(tab[0]))
	{
		if (is_dir(env, tab[1]))
		{
			if (is_reg(tab[2]))
			{
				env->champ_size += 8;
				return (1);
			}
		}
		else if (is_ind(env, tab[1]))
		{
			if (is_reg(tab[2]))
			{
				env->champ_size += 6;
				return (1);
			}
		}
		else if (is_reg(tab[1]))
			if (is_reg(tab[2]))
			{
				env->champ_size += 5;
				return (1);
			}
	}
	return (0);
}

char	check_ldi(t_env *env, char **tab)
{
	if (!tab[0] || ! tab[1] || !tab[2])
		return (0);
	while (*tab[0] < 33)
		tab[0]++;
	while (*tab[1] < 33)
		tab[1]++;
	while (*tab[2] < 33)
		tab[2]++;
	if (is_reg(tab[0]))
	{
		if (is_dir(env, tab[1]))
		{
			if (is_reg(tab[2]))
			{
				env->champ_size += 6;
				return (1);
			}
		}
		else if (is_reg(tab[1]))
			if (is_reg(tab[2]))
			{
				env->champ_size += 5;
				return (1);
			}
	}
	else if (is_ind(env, tab[0]))
	{
		if (is_dir(env, tab[1]))
		{
			if (is_reg(tab[2]))
			{
				env->champ_size += 7;
				return (1);
			}
		}
		else if (is_reg(tab[1]))
			if (is_reg(tab[2]))
			{
				env->champ_size += 6;
				return (1);
			}
	}
	else if (is_dir(env, tab[0]))
	{
		if (is_dir(env, tab[1]))
		{
			if (is_reg(tab[2]))
			{
				env->champ_size += 7;
				return (1);
			}
		}
		else if (is_reg(tab[1]))
			if (is_reg(tab[2]))
			{
				env->champ_size += 6;
				return (1);
			}
	}
	return (0);
}

char	check_sti(t_env *env, char **tab)
{
	if (!tab[0] || ! tab[1] || !tab[2])
		return (0);
	while (*tab[0] < 33)
		tab[0]++;
	while (*tab[1] < 33)
		tab[1]++;
	while (*tab[2] < 33)
		tab[2]++;
	if (is_reg(tab[0]))
	{
		if (is_dir(env, tab[1]))
		{
			if (is_dir(env, tab[2]))
			{
				env->champ_size += 7;
				return (1);
			}
			else if (is_reg(tab[2]))
			{
				env->champ_size += 6;
				return (1);
			}
		}
		else if (is_ind(env, tab[1]))
		{
			if (is_dir(env, tab[2]))
			{
				env->champ_size += 7;
				return (1);
			}
			else if (is_reg(tab[2]))
			{
				env->champ_size += 6;
				return (1);
			}
		}
		else if (is_reg(tab[1]))
		{
			if (is_dir(env, tab[2]))
			{
				env->champ_size += 6;
				return (1);
			}
			else if (is_reg(tab[2]))
			{
				env->champ_size += 5;
				return (1);
			}
		}
	}
	return (0);
}
