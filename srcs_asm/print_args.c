/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abassibe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/26 03:27:40 by abassibe          #+#    #+#             */
/*   Updated: 2018/01/26 03:34:01 by abassibe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

void	print_ind(t_env *env, const char *str, int i)
{
	int		tab[1];

	if (str[i] == ':')
	{
		tab[0] = (locate_label(env->label, &str[i + 1]) >> 8 & 0x00ff00ff) |
			(0xff00ff00 & locate_label(env->label, &str[i + 1]) << 8);
		write(FD, tab, 2);
	}
	else
	{
		if ((tab[0] = ft_atoi(&str[i])) < 0)
			tab[0] += 65536;
		tab[0] = (tab[0] >> 8 & 0x00ff00ff) | (0xff00ff00 & tab[0] << 8);
		write(FD, tab, 2);
	}
}

void	print_dir2(t_env * env, const char *str, int i, int dir_size)
{
	int		tab[1];

	if (dir_size == 4)
	{
		if ((tab[0] = ft_atoi(&str[i + 1])) < 0 )
			tab[0] = 4294967296 + tab[0];
		tab[0] = switch_int(tab[0]);
		write(FD, tab, 4);
	}
	else if (dir_size == 2)
	{
		if ((tab[0] = ft_atoi(&str[i + 1])) < 0)
			tab[0] = 65536 + tab[0];
		tab[0] = (tab[0] >> 8 & 0x00ff00ff) | (0xff00ff00 & tab[0] << 8);
		write(FD, tab, 2);
	}
}

void	print_dir(t_env * env, const char *str, int i, int dir_size)
{
	int		tab[1];

	if (str[i + 1] == ':')
	{
		if (dir_size == 4)
		{
			tab[0] = switch_int(locate_label(env->label, &str[i + 2]));
			write(FD, tab, 4);
		}
		else
		{
			tab[0] = (locate_label(env->label, &str[i + 2]) >> 8 & 0x00ff00ff) |
				(0xff00ff00 & locate_label(env->label, &str[i + 2]) << 8);
			write(FD, tab, 2);
		}
	}
	else
		print_dir2(env, str, i, dir_size);
}
