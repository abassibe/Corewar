/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_core.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abassibe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/17 02:33:43 by abassibe          #+#    #+#             */
/*   Updated: 2018/01/17 05:38:35 by abassibe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

static char		is_label(t_env *env, const char *str, int i)
{
	int		j;

	j = -1;
	while (++j < 16)
		if (ft_strnstr(str, env->op[j], i))
			return (0);
	return (1);
}

static void		save_label(t_env *env, const char *str, int i)
{
	t_label		*tmp;

	if (!env->label)
	{
		env->label = ft_memalloc(sizeof(t_label));
		env->label->label_name = ft_strndup(str, i);
	}
	else
	{
		tmp = env->label;
		while (env->label->next)
			env->label = env->label->next;
		env->label->next = ft_memalloc(sizeof(t_label));
		env->label = env->label->next;
		env->label->label_name = ft_strndup(str, i);
		env->label = tmp;
	}
}

char			save_ulabel(t_env *env, const char *str)
{
	t_ulabel	*tmp;

	if (!*str)
		return (0);
	if (!env->ulab)
	{
		env->ulab = (t_ulabel *)ft_memalloc(sizeof(t_ulabel));
		env->ulab->label = ft_strdup(str);
	}
	else
	{
		tmp = env->ulab;
		while (env->ulab->next)
			env->ulab = env->ulab->next;
		env->ulab->next = (t_ulabel *)ft_memalloc(sizeof(t_ulabel));
		env->ulab->next->label = ft_strdup(str);
		env->ulab = tmp;
	}
	return (1);
}

char			is_dir(t_env *env, const char *str)
{
	while (*str && *str != '%')
		str++;
	str++;
	if (*str == '-')
		str++;
	if (*str >= '0' && *str <= '9')
	{
		while (*str && (*str >= '0' && *str <= '9'))
			str++;
		while (*str && *str != '#')
		{
			if (*str > 33 && *str != '#')
				return (0);
			str++;
		}
		return (1);
	}
	else if (*str == ':')
	{
		if (!save_ulabel(env, &str[1]))
			return (0);
		return (1);
	}
	return (0);
}

char			is_reg(t_env *env, const char *str)
{
	env->name = 1;
	printf("reg = %s\n", str);
	return (1);
}
char			is_ind(t_env *env, const char *str)
{
	env->name = 1;
	printf("ind = %s\n", str);
	return (1);
}

char			check_dir_ind(t_env *env, const char *str)
{
	if (is_dir(env, str))
	{
		while (*str != ',')
			str++;
		str++;
		if (is_reg(env, str))
			return (1);
		return (0);
	}
	if (is_ind(env, str))
	{
		while (*str != ',')
			str++;
		str++;
		if (is_reg(env, str))
			return (1);
		return (0);
	}
	return (0);
}

static char		get_op(t_env *env, const char *str)
{
	while (*str < 33)
		str++;
	if (str[0] == 'l' && str[1] == 'i' && str[2] == 'v' && str[3] == 'e' && (str[4] < 33 || str[4] == '%'))
	{
		if (!is_dir(env, &str[4]))
			return (0);
	}
	else if (str[0] == 'l' && str[1] == 'd' && (str[2] < 33 || str[2] == '%'))
	{
		if (!check_dir_ind(env, &str[2]))
			return (0);
	}
	else if (str[0] == 's' && str[1] == 't' && str[2] < 33)
		return (1);
	else if (str[0] == 'a' && str[1] == 'd' && str[2] == 'd' && str[3] < 33)
		return (1);
	else if (str[0] == 's' && str[1] == 'u' && str[2] == 'b' && str[3] < 33)
		return (1);
	else if (str[0] == 'a' && str[1] == 'n' && str[2] == 'd' && (str[3] < 33 || str[3] == '%'))
		return (1);
	else if (str[0] == 'o' && str[1] == 'r' && (str[2] < 33 || str[2] == '%'))
		return (1);
	else if (str[0] == 'x' && str[1] == 'o' && str[2] == 'r' && (str[3] < 33 || str[3] == '%'))
		return (1);
	else if (str[0] == 'z' && str[1] == 'j' && str[2] == 'm' && str[3] == 'p' && (str[4] < 33 || str[4] == '%'))
		return (1);
	else if (str[0] == 'l' && str[1] == 'd' && str[2] == 'i' && (str[3] < 33 || str[3] == '%'))
		return (1);
	else if (str[0] == 's' && str[1] == 't' && str[2] == 'i' && str[3] < 33)
		return (1);
	else if (str[0] == 'f' && str[1] == 'o' && str[2] == 'r' && str[3] == 'k' && (str[4] < 33 || str[4] == '%'))
		return (1);
	else if (str[0] == 'l' && str[1] == 'l' && str[2] == 'd' && (str[3] < 33 || str[3] == '%'))
		return (1);
	else if (str[0] == 'l' && str[1] == 'l' && str[2] == 'd' && str[3] == 'i' && (str[4] < 33 || str[4] == '%'))
		return (1);
	else if (str[0] == 'l' && str[1] == 'f' && str[2] == 'o' && str[3] == 'r' && str[4] == 'k' && (str[5] < 33 || str[5] == '%'))
		return (1);
	else if (str[0] == 'a' && str[1] == 'f' && str[2] == 'f' && str[3] < 33)
		return (1);
	return (1);
}

char			pars_core(t_env *env, const char *str)
{
	int		i;

	i = 0;
	alloc_operators(env);
	if (comment_or_empty(str))
		return (1);
	while (*str < 33)
		str++;
	while (str[i] && str[i] != ':' && str[i] != ' ' && str[i] != ',' &&
			str[i] != '%')
	{
		i++;
		if (!str[i])
			return (0);
		if (str[i] == ':')
		{
			if (is_label(env, str, i))
			{
				save_label(env, str, i);
				if (!get_op(env, &str[i + 1]))
					return (0);
			}
		}
		else if (str[i] == ' ' || str[i] == ',' || str[i] == '%')
			if (!get_op(env, str))
				return (0);
	}
	return (1);
}
