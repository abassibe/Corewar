/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abassibe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/13 03:10:10 by abassibe          #+#    #+#             */
/*   Updated: 2018/01/19 06:15:51 by abassibe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

static void		check_header(t_env *env, const char *str)
{
	int		i;
	int		count;

	count = 0;
	i = 4;
	if (str[1] == 'n' && str[2] == 'a' && str[3] == 'm' && str[4] == 'e')
	{
		while (str[i] && str[i] != '"')
			i++;
		if (!str[i] || !str[i + 1])
			ft_error("No champion name", 0);
		i++;
		while (str[i] && str[i] != '"')
		{
			write(FD, &str[i], 1);
			i++;
			count++;
			if (count > 127)
				ft_error("Champion name too long", 0);
		}
		if (!str[i] || str[i] != '"')
			ft_error("Wrong format champion name", 0);
	}
}

static void		parsing(t_env *env, const char *str)
{
	int		i;

	i = 0;
	while (str[i] && str[i] < 33)
		i++;
	while (str[i])
	{
		if (str[i] == '#')
			break ;
		if (str[i] == '.')
			check_header(env, &str[i]);
		i++;
	}
	i = env->fd;
}

void			kingdom_hearts(t_env *env)
{
	char	*str;
	int		*magic;

	return ;
	if (!(magic = malloc(sizeof(int))))
		ft_error("", 1);
	magic[0] = 0xf383ea00;
	env->bin_name = creat_bin(env->file_name);
	if ((FD = open(env->bin_name, O_CREAT | O_RDWR, 0777)) == -1)
		ft_error("", 1);
	write(FD, magic, 4);
	while (get_next_line(env->fd, &str))
	{
		parsing(env, str);
	}
	free(magic);
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

	if ((env->fd = open(file_name, O_RDONLY)) == -1)
	{
		write(2, "No such file or directory\n", 26);
		return (0);
	}
	env->file_name = ft_strdup(file_name);
	alloc_operators(env);
	while (get_next_line(env->fd, &str))
	{
		if (!parseur_next(env, str))
		{
			ft_strdel(&str);
			return (0);
		}
		ft_strdel(&str);
	}
	return (1);
}
