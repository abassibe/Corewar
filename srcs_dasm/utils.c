/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abassibe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/02 00:45:53 by abassibe          #+#    #+#             */
/*   Updated: 2018/02/02 03:39:58 by abassibe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/dasm.h"

void	ft_error(const char *str, const int check)
{
	if (check == 0)
		ft_printf("%s\n", str);
	else
		perror("");
	exit (-1);
}

char	*creat_bin(const char *str)
{
	char	**tab;
	char	*tmp;

	tab = ft_strsplit(str, '.');
//	tmp = ft_strjoin(tab[0], ".s");
	tmp = ft_strjoin("test", ".s");
	free(tab[0]);
	free(tab[1]);
	free(tab);
	return (tmp);
}

void	clear_buff(char *buff)
{
	int		i;

	i = -1;
	while (buff[++i])
		buff[i] = 0;
}
