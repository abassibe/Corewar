/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_core.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abassibe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/17 02:33:43 by abassibe          #+#    #+#             */
/*   Updated: 2018/01/19 04:41:37 by abassibe         ###   ########.fr       */
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

char			pars_core(t_env *env, const char *s)
{
	int		i;

	i = 0;
	if (comment_or_empty(s))
		return (1);
	while (*s < 33)
		s++;
	while (s[i] && s[i] != ':' && s[i] != ' ' && s[i] != ',' && s[i] != '%')
	{
		i++;
		if (!s[i])
			return (0);
		if (s[i] == ':')
		{
			if (is_label(env, s, i))
				save_label(env, s, i);
			if (!get_op1(env, &s[i + 1]))
				return (0);
		}
		else if (s[i] == ' ' || s[i] == ',' || s[i] == '%')
			if (!get_op1(env, s))
				return (0);
	}
	return (1);
}
