/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_ld_live.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abassibe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/26 01:39:18 by abassibe          #+#    #+#             */
/*   Updated: 2018/01/30 03:18:25 by abassibe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

void			print_live(t_env *env, const char *str)
{
	int		tab[1];

	tab[0] = 0x00000001;
	write(FD, tab, 1);
	while (*str != '%')
		str++;
	if (str[1] != ':')
	{
		if ((tab[0] = ft_atoi(&str[1])) < 0)
			tab[0] = 4294967296 + tab[0];
	}
	else
		tab[0] = locate_label(env->label, &str[2]);
	tab[0] = switch_int(tab[0]);
	write(FD, tab, 4);
}

void			print_ld(t_env *env, const char *str)
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
		print_dir(env, str, i, 4);
	}
	else if (is_ind_print(str, &i))
	{
		tab[0] = 0xd0;
		write(FD, tab, 1);
		print_ind(env, str, i);
	}
	while (str[i] != ',')
		i++;
	while (str[i] != 'r')
		i++;
	tab[0] = ft_atoi(&str[i + 1]);
	write(FD, tab, 1);
}

static void		print_st2(t_env *env, const char *str, int i, int save)
{
	int		tab[1];

	tab[0] = 0x50;
	write(FD, tab, 1);
	tab[0] = ft_atoi(&str[save + 1]);
	write(FD, tab, 1);
	while (str[i] != ',')
		i++;
	i++;
	while (str[i] < 33)
		i++;
	tab[0] = ft_atoi(&str[i + 1]);
	write(FD, tab, 1);
}

void			print_st(t_env *env, const char *str)
{
	int		tab[1];
	int		i;
	int		save;

	tab[0] = 0x00000003;
	write(FD, tab, 1);
	i = 0;
	while (str[i] != 'r')
		i++;
	save = i;
	if (is_ind_print(str, &i))
	{
		tab[0] = 0x70;
		write(FD, tab, 1);
		tab[0] = ft_atoi(&str[save + 1]);
		write(FD, tab, 1);
		print_ind(env, str, i);
	}
	else
		print_st2(env, str, i, save);
}

void			print_add(t_env *env, const char *str)
{
	int		tab[1];
	int		i;

	tab[0] = 0x00000004;
	write(FD, tab, 1);
	i = 0;
	tab[0] = 0x54;
	write(FD, tab, 1);
	while (str[i] != 'r')
		i++;
	i++;
	tab[0] = ft_atoi(&str[i]);
	write(FD, tab, 1);
	while (str[i] != 'r')
		i++;
	i++;
	tab[0] = ft_atoi(&str[i]);
	write(FD, tab, 1);
	while (str[i] != 'r')
		i++;
	tab[0] = ft_atoi(&str[i + 1]);
	write(FD, tab, 1);
}
