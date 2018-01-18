/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_op.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abassibe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/18 04:40:10 by abassibe          #+#    #+#             */
/*   Updated: 2018/01/18 05:27:05 by abassibe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

static char		get_op5(t_env *env, const char *str, char **tab)
{
	if (str[0] == 's' && str[1] == 'u' && str[2] == 'b' && str[3] < 33)
	{
		while (*str && *str != 'r')
			str++;
		tab = ft_strsplit(str, ',');
		if (!check_add(tab))
		{
			free_tab(tab, 3);
			return (0);
		}
		free_tab(tab, 3);
		return (1);
	}
	return (get_op6(env, str, tab));
}

static char		get_op4(t_env *env, const char *str, char **tab)
{
	if (str[0] == 'a' && str[1] == 'd' && str[2] == 'd' && str[3] < 33)
	{
		while (*str && *str != 'r')
			str++;
		tab = ft_strsplit(str, ',');
		if (!check_add(tab))
		{
			free_tab(tab, 3);
			return (0);
		}
		free_tab(tab, 3);
		return (1);
	}
	return (get_op5(env, str, tab));
}

static char		get_op3(t_env *env, const char *str, char **tab)
{
	if (str[0] == 's' && str[1] == 't' && str[2] < 33)
	{
		while (*str && *str != 'r')
			str++;
		tab = ft_strsplit(str, ',');
		if (!check_st(env, tab))
		{
			free_tab(tab, 2);
			return (0);
		}
		free_tab(tab, 2);
		return (1);
	}
	return (get_op4(env, str, tab));
}

static char		get_op2(t_env *env, const char *str, char **tab)
{
	if (str[0] == 'l' && str[1] == 'd' && (str[2] < 33 || str[2] == '%' ||
				str[2] == ':'))
	{
		while (*str && *str != ':' && (*str < '0' || *str > '9') &&
				*str != '-' && *str != '%')
			str++;
		tab = ft_strsplit(str, ',');
		if (!check_ld(env, tab))
		{
			free_tab(tab, 2);
			return (0);
		}
		free_tab(tab, 2);
		return (1);
	}
	return (get_op3(env, str, tab));
}

char			get_op1(t_env *env, const char *str)
{
	char	**tab;

	tab = NULL;
	while (*str < 33)
		str++;
	if (str[0] == 'l' && str[1] == 'i' && str[2] == 'v' && str[3] == 'e' &&
			(str[4] < 33 || str[4] == '%'))
	{
		while (*str && *str != '%')
			str++;
		if (!is_dir(env, str))
			return (0);
		return (1);
	}
	return (get_op2(env, str, tab));
}
