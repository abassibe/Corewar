/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abassibe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/12 02:22:44 by abassibe          #+#    #+#             */
/*   Updated: 2018/01/16 05:49:47 by abassibe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

void	ft_error(const char *str, const int check)
{
	if (check == 0)
		ft_printf("%s\n", str);
	else
		perror("");
	exit(-1);
}

int		main(int ac, char **av)
{
	int		i;
	int		fd;
	t_env	env;

	i = 0;
	fd = 0;
	if (ac < 2)
		ft_error("No argument", 0);
	while (++i < ac)
	{
		if (parseur(&env, av[i]))
			kingdom_hearts(&env, fd);
		else
			ft_printf("{red}An error occured with '%s'\n", av[i]);
	}
}
