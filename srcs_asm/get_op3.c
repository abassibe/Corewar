/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_op3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abassibe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/18 04:40:10 by abassibe          #+#    #+#             */
/*   Updated: 2018/01/18 05:26:46 by abassibe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

static char		get_op15(t_env *env, const char *str)
{
	if (str[0] == 'l' && str[1] == 'f' && str[2] == 'o' && str[3] == 'r' &&
			str[4] == 'k' && (str[5] < 33 || str[5] == '%'))
	{
		while (*str && *str != '%')
			str++;
		if (!is_dir(env, str))
			return (0);
		return (1);
	}
	else if (str[0] == 'a' && str[1] == 'f' && str[2] == 'f' && str[3] < 33)
	{
		while (*str && *str != 'r')
			str++;
		if (!is_reg(str))
			return (0);
		return (1);
	}
	return (0);
}

static char		get_op14(t_env *env, const char *str, char **tab)
{
	if (str[0] == 'l' && str[1] == 'l' && str[2] == 'd' &&
			str[3] == 'i' && (str[4] < 33 || str[4] == '%' || str[4] == ':'))
	{
		while (*str && *str != ':' && (*str < '0' || *str > '9') &&
				*str != '-' && *str != '%')
			str++;
		tab = ft_strsplit(str, ',');
		if (!check_ldi(env, tab))
		{
			free_tab(tab, 3);
			return (0);
		}
		free_tab(tab, 3);
		return (1);
	}
	return (get_op15(env, str));
}

static char		get_op13(t_env *env, const char *str, char **tab)
{
	if (str[0] == 'l' && str[1] == 'l' && str[2] == 'd' &&
			(str[3] < 33 || str[3] == '%' || str[2] == ':'))
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
	return (get_op14(env, str, tab));
}

static char		get_op12(t_env *env, const char *str, char **tab)
{
	if (str[0] == 'f' && str[1] == 'o' && str[2] == 'r' &&
			str[3] == 'k' && (str[4] < 33 || str[4] == '%'))
	{
		while (*str && *str != '%')
			str++;
		if (!is_dir(env, str))
			return (0);
		return (1);
	}
	return (get_op13(env, str, tab));
}

char			get_op11(t_env *env, const char *str, char **tab)
{
	if (str[0] == 's' && str[1] == 't' && str[2] == 'i' && str[3] < 33)
	{
		while (*str && *str != 'r')
			str++;
		tab = ft_strsplit(str, ',');
		if (!check_sti(env, tab))
		{
			free_tab(tab, 3);
			return (0);
		}
		free_tab(tab, 3);
		return (1);
	}
	return (get_op12(env, str, tab));
}
