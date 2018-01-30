/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_sub_zjmp_fork.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abassibe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/26 04:57:59 by abassibe          #+#    #+#             */
/*   Updated: 2018/01/30 05:30:45 by abassibe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

void			print_sub(t_env *env, const char *str)
{
	int		tab[1];
	int		i;

	tab[0] = 0x00000005;
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

void			print_zjmp(t_env *env, const char *str)
{
	int		tab[1];

	tab[0] = 0x00000009;
	write(FD, tab, 1);
	while (*str != '%')
		str++;
	if (str[1] != ':')
	{
		if ((tab[0] = ft_atoi(&str[1])) < 0)
			tab[0] = 65536 + tab[0];
	}
	else
		tab[0] = locate_label(env->label, &str[2]);
	tab[0] = (tab[0] >> 8 & 0x00ff00ff) | (0xff00ff00 & tab[0] << 8);
	write(FD, tab, 2);
}

void			print_fork(t_env *env, const char *str)
{
	int		tab[1];

	tab[0] = 0x0000000c;
	write(FD, tab, 1);
	while (*str != '%')
		str++;
	if (str[1] != ':')
	{
		if ((tab[0] = ft_atoi(&str[1])) < 0)
			tab[0] = 65536 + tab[0];
	}
	else
		tab[0] = locate_label(env->label, &str[2]);
	tab[0] = (tab[0] >> 8 & 0x00ff00ff) | (0xff00ff00 & tab[0] << 8);
	write(FD, tab, 2);
}

void			print_lfork(t_env *env, const char *str)
{
	int		tab[1];

	tab[0] = 0x0000000f;
	write(FD, tab, 1);
	while (*str != '%')
		str++;
	if (str[1] != ':')
	{
		if ((tab[0] = ft_atoi(&str[1])) < 0)
			tab[0] = 65536 + tab[0];
	}
	else
		tab[0] = locate_label(env->label, &str[2]);
	tab[0] = (tab[0] >> 8 & 0x00ff00ff) | (0xff00ff00 & tab[0] << 8);
	write(FD, tab, 2);
}

void			print_lld(t_env *env, const char *str)
{
	int		tab[1];
	int		i;

	if (str[3] == 'i')
		return ;
	tab[0] = 0x0000000d;
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
