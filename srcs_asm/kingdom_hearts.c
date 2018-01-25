/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kingdom_hearts.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abassibe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/23 02:58:23 by abassibe          #+#    #+#             */
/*   Updated: 2018/01/25 06:30:23 by abassibe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

void	print_live(t_env *env, const char *str)
{
	int		tab[1];

	tab[0] = 0x00000001;
	write(FD, tab, 4);
	while (*str != '%')
		str++;
	if (str[1] != ':')
	{
		tab[0] = ft_atoi(&str[1]);
		write(FD, tab, 1);
	}
	else
	{
		tab[0] = env->champ_size;
		write(FD, tab, 1);
	}
}

int		is_dir_print(const char *str, int *i)
{
	int		save;

	save = *i;
	while (str[*i] != '%')
	{
		if (!str[*i] || str[*i] == ',')
			break ;
		(*i)++;
	}
	if (str[*i] == '%')
		return (1);
	*i = save;
	return (0);
}

int		is_ind_print(const char *str, int *i)
{
	int		save;

	save = *i;
	while (str[*i] < 33)
		(*i)++;
	while (str[*i] > 33)
		(*i)++;
	while (str[*i] < 33)
		(*i)++;
	if (str[*i] == ':' || (str[*i] >= '0' && str[*i] <= '9'))
		return (1);
	*i = save;
	return (0);
}

int		locate_label(t_label *label, const char *str)
{
	while (label)
	{
		if (ft_strnstr(str, label->label_name, ft_strlen(label->label_name)))
			return (label->pos);
		label = label->next;
	}
	return (0);
}

void	print_ld(t_env *env, const char *str)
{
	int		tab[1];
	int		i;

	tab[0] = 0x00000002;
	i = 0;
	write(FD, tab, 1);
	if (is_dir_print(str, &i))
	{
		tab[0] = 0x90;
		write(FD, tab, 1);
		if (str[i + 1] == ':')
		{
			tab[0] = switch_int(locate_label(env->label, &str[i]));
			write(FD, tab, 4);
		}
		else
		{
			tab[0] = switch_int(ft_atoi(&str[i + 1]));
			write(FD, tab, 4);
		}
	}
	else if (is_ind_print(str, &i))
	{
		tab[0] = 0xd0;
		write(FD, tab, 1);
		tab[0] = (locate_label(env->label, &str[i + 1]) >> 8 & 0x00ff00ff) |
			(0xff00ff00 & locate_label(env->label, &str[i + 1]) << 8);
		write(FD, tab, 2);
	}
	while (str[i] != ',')
		i++;
	while (str[i] != 'r')
		i++;
	tab[0] = ft_atoi(&str[i + 1]);
	write(FD, tab, 1);
}

void	print_op(t_env *env, const char *str)
{
	int		i;

	i = -1;
	while (++i < 16)
		if (ft_strnstr(str, env->op[i], ft_strlen(env->op[i])))
		{
			env->opf[i](env, str);
		}
}

void	print_core(t_env *env, const char *str)
{
	int		i;

	i = 0;
	alloc_op_functions(env);
	while (*str < 33)
		str++;
	if (i == 2)
		;
//	if (is_label(env, str, i))
//		fonction_du_label();
	else
		print_op(env, str);
}

void	dispatcher(t_env *env, const char *str)
{
	if (comment_or_empty(str))
		return ;
	if (env->name == 0 || env->comment == 0)
		print_name_comment(env, str);
	else
		print_core(env, str);
}

void	kingdom_hearts(t_env *env)
{
	char	*str;
	int		*magic;

	if (!(magic = malloc(sizeof(int))))
		ft_error("", 1);
	magic[0] = 0xf383ea00;
	env->bin_name = creat_bin(env->file_name);
	if ((FD = open(env->bin_name, O_CREAT | O_RDWR, 0777)) == -1)
		ft_error("", 1);
	write(FD, magic, 4);
	lseek(env->fd, 0, SEEK_SET);
	env->name = 0;
	env->comment = 0;
	while (get_next_line(env->fd, &str))
	{
		dispatcher(env, str);
	}
	free(magic);
}
