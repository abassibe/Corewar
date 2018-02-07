/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   diff.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abassibe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/07 02:38:21 by abassibe          #+#    #+#             */
/*   Updated: 2018/02/07 04:11:51 by abassibe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include "../includes/libft.h"

char	get_diff(int fd1, int fd2)
{
	char	*str1;
	char	*str2;
	int		ret1;
	int		ret2;
	int		octet;
	int		nl;

	octet = 0;
	str1 = ft_strnew(1);
	str2 = ft_strnew(1);
	nl = 0;
	while (1)
	{
		ret1 = read(fd1, str1, 1);
		ret2 = read(fd2, str2, 1);
		if (ret1 < 1 || ret2 < 1)
			break ;
		if (str1[0] != str2[0])
		{
			printf("Difference a l'octet %d :\n", octet);
			ft_printf("{red}[%4d]|[%-4d] | ", str1[0], str2[0]);
			exit (-1);
		}
		ft_printf("{green}[%4d]|[%-4d]", str1[0], str2[0]);
		nl++;
		if (nl >= 8)
		{
			printf("\n");
			nl = 0;
		}
		else
			ft_printf("{blue} ||| ");
		octet++;
	}
	if (ret1 == 0 && ret2 == 0)
	{
		printf("\n");
		return (1);
	}
	if (ret1 > 0)
	{
		ft_printf("{red}[%4d]|[NULL]", str1[0]);
		while ((ret1 = read(fd1, str1, 1)))
		{
			ft_printf("{red}[%4d]|[NULL]", str1[0]);
			if (nl >= 8)
			{
				printf("\n");
				nl = 0;
			}
			else
			ft_printf("{blue} ||| ");
			octet++;
		}
	}
	if (ret2 > 0)
	{
		ft_printf("{red}[NULL]|[%-4d]", str1[0], str2[0]);
		while ((ret1 = read(fd1, str1, 1)))
		{
			ft_printf("{red}[NULL]|[%-4d]", str1[0], str2[0]);
			if (nl >= 8)
			{
				printf("\n");
				nl = 0;
			}
			else
			ft_printf("{blue} ||| ");
			octet++;
		}
	}
	printf("\n");
	return (0);
}

int		main(int ac, char **av)
{
	int		fd1;
	int		fd2;

	if (ac != 3)
		return (-1);
	if ((fd1 = open(av[1], O_RDONLY)) == -1)
	{
		perror("");
		return (0);
	}
	if ((fd2 = open(av[2], O_RDONLY)) == -1)
	{
		perror("");
		return (0);
	}
	return (get_diff(fd1, fd2));
}
