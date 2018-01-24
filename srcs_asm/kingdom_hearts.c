/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kingdom_hearts.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abassibe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/23 02:58:23 by abassibe          #+#    #+#             */
/*   Updated: 2018/01/24 05:44:49 by abassibe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

void	print_champ_size(t_env *env)
{
	int		*tab;
	int		tmp;

	tmp = env->champ_size;
	tmp = (tmp >> 16 & 0x0000ffff) | (0xffff0000 & tmp << 16);
	tmp = (tmp >> 8 & 0x00ff00ff) | (0xff00ff00 & tmp << 8);
	if (!(tab = malloc(sizeof(int))))
		ft_error("", 1);
	tab[0] = tmp;
	write(FD, tab, 4);
}

void	print_name(t_env *env, const char *str)
{
	int		i;
	int		limit;
	int		tab[1];

	i = 5;
	limit = -1;
	while (str[i] && str[i] != '"')
		i++;
	i++;
	while (str[i] && str[i] != '"')
	{
		tab[0] = str[i];
		write(FD, tab, 1);
		i++;
		limit++;
	}
	while (++limit < 128)
		write(FD, "\0", 1);
	write(FD, "\0\0\0\0", 4);
	print_champ_size(env);
}

void	print_comment(t_env *env, const char *str)
{
	int		i;
	int		limit;
	int		tab[1];

	i = 5;
	limit = -1;
	while (str[i] && str[i] != '"')
		i++;
	i++;
	while (str[i] && str[i] != '"')
	{
		tab[0] = str[i];
		write(FD, tab, 1);
		i++;
		limit++;
	}
	while (++limit < 2048)
		write(FD, "\0", 1);
	write(FD, "\0\0\0\0", 4);
}

void	print_name_comment(t_env *env, const char *str)
{
	while (*str && *str != '.')
		str++;
	if (!*str)
		return ;
	if (str[1] == 'n' && str[2] == 'a' && str[3] == 'm' && str[4] == 'e')
	{
		print_name(env, str);
		env->name = 1;
	}
	if (str[1] == 'c' && str[2] == 'o' && str[3] == 'm' && str[4] == 'm' &&
			str[5] == 'e' && str[6] == 'n' && str[7] == 't')
	{
		print_comment(env, str);
		env->comment = 1;
	}
}

void	print_core(t_env *env, const char *str)
{
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
