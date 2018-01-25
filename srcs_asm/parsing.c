/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abassibe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/13 03:10:10 by abassibe          #+#    #+#             */
/*   Updated: 2018/01/25 02:56:05 by abassibe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

char			nl_end_of_file(int fd)
{
	char	*str;

	str = ft_strnew(1);
	lseek(fd, -1, SEEK_END);
	read(fd, str, 1);
	if (*str != '\n')
	{
		ft_strdel(&str);
		write(2, "No new line at the end of the file\n", 35);
		return (0);
	}
	ft_strdel(&str);
	return (1);
}

char			label_verif(t_env *env)
{
	t_label		*tmp;

	tmp = env->label;
	if (!env->ulab || !env->label)
		return (1);
	while (env->ulab)
	{
		while (env->label)
		{
			if (!ft_strcmp(env->label->label_name, env->ulab->label))
				break ;
			if (!env->label->next)
				return (0);
			env->label = env->label->next;
		}
		env->label = tmp;
		env->ulab = env->ulab->next;
	}
	return (1);
}

char			parseur_next(t_env *env, char *str)
{
	if (env->name == 0 || env->comment == 0)
	{
		if (!pars_name_comment(env, str))
			return (0);
	}
	else if (!pars_core(env, str))
		return (0);
	return (1);
}

char			parseur(t_env *env, const char *file_name)
{
	char	*str;
	int		value;

	if ((env->fd = open(file_name, O_RDONLY)) == -1)
	{
		write(2, "No such file or directory\n", 26);
		return (0);
	}
	env->file_name = ft_strdup(file_name);
	while ((value = get_next_line(env->fd, &str)) > 0)
	{
		if (!parseur_next(env, str) || env->champ_size > CHAMP_MAX_SIZE)
		{
			if (env->champ_size > CHAMP_MAX_SIZE)
				ft_printf("\"%s\" : Champion too big\n", file_name);
			ft_strdel(&str);
			return (0);
		}
		ft_strdel(&str);
	}
	ft_strdel(&str);
	if (value == -1 || !nl_end_of_file(env->fd) || !label_verif(env))
		return (0);
	return (1);
}
