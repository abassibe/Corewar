/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abassibe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/13 03:10:10 by abassibe          #+#    #+#             */
/*   Updated: 2018/01/16 05:49:24 by abassibe         ###   ########.fr       */
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

void			kingdom_hearts(t_env *env, const int fd)
{
	char	*str;
	int		*magic;

	if (!(magic = malloc(sizeof(int))))
		ft_error("", 1);
	magic[0] = 0xf383ea00;
	env->bin_name = creat_bin(env->file_name);
	remove(env->bin_name);
	if ((FD = open(env->bin_name, O_CREAT | O_RDWR, 0777)) == -1)
		ft_error("", 1);
	write(FD, magic, 4);
	while (get_next_line(fd, &str))
	{
		parsing(env, str);
	}
	free(magic);
}

char			is_label(t_env *env, const char *str, int i)
{
	int		j;

	j = -1;
	while (++j < 16)
		if (ft_strnstr(str, env->op[j], i))
			return (0);
	return (1);
}

void			save_label(t_env *env, const char *str, int i)
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

char			get_op(t_env *env, const char *str, int i)
{
	env->name = 1;
	i = 0;
	printf("%s\n", str);
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
	while (str[i] && str[i] != ':' && str[i] != ' ' && str[i] != ',' && str[i] != '%')
	{
		i++;
		if (str[i] == ':')
		{
			if (is_label(env, str, i))
			{
				save_label(env, str, i);
				if (!get_op(env, &str[i + 1], i))
					return (0);
			}
		}
		else if (str[i] == ' ' || str[i] == ',' || str[i] == '%')
			if (!get_op(env, &str[i + 1], i))
				return (0);
	}
	return (1);
}

char			parseur(t_env *env, const char *file_name)
{
	char	*str;
	int		fd;

	if ((fd = open(file_name, O_RDONLY)) == -1)
	{
		write(2, "No such file or directory\n", 26);
		return (0);
	}
	env->file_name = ft_strdup(file_name);
	while (get_next_line(fd, &str))
	{
		if (env->name == 0 || env->comment == 0)
		{
			if (!pars_name_comment(env, str))
			{
				free(env->file_name);
				free(str);
				close(fd);
				return (0);
			}
		}
		else if (!pars_core(env, str))
		{
			free(env->file_name);
			//free la liste des labels
			free(str);
			close(fd);
			return (0);
		}
		free(str);
	}
	return (1);
}
