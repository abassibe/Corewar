/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_sub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abassibe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/26 04:57:59 by abassibe          #+#    #+#             */
/*   Updated: 2018/01/26 06:09:44 by abassibe         ###   ########.fr       */
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

void			print_reg(t_env *env, const char *str, int *i)
{
	int		tab[1];

	while (str[*i] && str[*i] != 'r')
		(*i)++;
	tab[0] = ft_atoi(&str[*i + 1]);
	write(FD, tab, 1);
}

void			print_and(t_env *env, const char *str)
{
	int		tab[1];
	int		i;
	int		save;

	tab[0] = 0x00000006;
	write(FD, tab, 1);
	i = 0;
	save = i;
	if (is_dir_print(str, &i))
	{
		save = i;
		while (str[i] != ',')
			i++;
		i++;
		if (is_dir_print(str, &i))
		{
			tab[0] = 0xa4;
			write(FD, tab, 1);
			print_dir(env, str, save, 4);
			print_dir(env, str, i, 4);
		}
		else if (is_ind_print(str, &i))
		{
			tab[0] = 0xb4;
			write(FD, tab, 1);
			print_dir(env, str, save, 4);
			print_ind(env, str, i);
		}
		else
		{
			tab[0] = 0x94;
			write(FD, tab, 1);
			print_dir(env, str, save, 4);
			print_reg(env, str, &i);
			i++;
		}
	}
	else if (is_ind_print(str, &i))
	{
		save = i;
		while (str[i] != ',')
			i++;
		i++;
		if (is_dir_print(str, &i))
		{
			tab[0] = 0xe4;
			write(FD, tab, 1);
			print_ind(env, str, save);
			print_dir(env, str, i, 4);
		}
		else if (is_ind_print(str, &i))
		{
			tab[0] = 0xf4;
			write(FD, tab, 1);
			print_ind(env, str, save);
			print_ind(env, str, i);
		}
		else
		{
			tab[0] = 0xd4;
			write(FD, tab, 1);
			print_ind(env, str, save);
			print_reg(env, str, &i);
			i++;
		}
	}
	else
	{
		while (str[i] != 'r')
			i++;
		save = i;
		while (str[i] != ',')
			i++;
		i++;
		if (is_dir_print(str, &i))
		{
			tab[0] = 0x64;
			write(FD, tab, 1);
			print_reg(env, str, &save);
			print_dir(env, str, i, 4);
		}
		else if (is_ind_print(str, &i))
		{
			tab[0] = 0x74;
			write(FD, tab, 1);
			print_reg(env, str, &save);
			print_ind(env, str, i);
		}
		else
		{
			tab[0] = 0x54;
			write(FD, tab, 1);
			print_reg(env, str, &save);
			print_reg(env, str, &i);
			i++;
		}
	}
	print_reg(env, str, &i);
}
