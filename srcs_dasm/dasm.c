/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dasmc.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abassibe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/01 04:08:31 by abassibe          #+#    #+#             */
/*   Updated: 2018/02/02 05:33:59 by abassibe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/dasm.h"

char	get_body(t_env *env)
{
	return (1);
}

char	start(t_env *env, const char *file_name)
{
	int		value;

	env->str = ft_strnew(2049);
	if ((env->fd_bin = open(file_name, O_RDONLY)) == -1)
		return (0);
	env->champ_s = creat_bin(file_name);
	remove(env->champ_s);
	if ((env->fd_champ = open(env->champ_s, O_WRONLY | O_CREAT, 0777)) == -1)
		return (0);
	if (!get_magic_number(env))
		return (0);
	if (value == -1)
	{
		perror("");
		return (0);
	}
	if (!get_header(env))
		return (0);
	if (!get_body(env))
		return (0);
	ft_strdel(&env->str);
	return (1);
}

int		main(int ac, char **av)
{
	int		i;
	t_env	*env;

	i = 0;
	if (ac < 2)
		ft_error("No argument", 0);
	if (ac > 2)
		ft_printf("\n{cyan}----------- Champions decompilation ----------\n\n");
	while (++i < ac)
	{
		env = (t_env *)ft_memalloc(sizeof(t_env));
		if (!start(env, av[i]))
		{
			ft_printf("{red}ERROR: %s : '%s'\n", env->error, av[i]);
			remove(env->champ_s);
		}
		else
			ft_printf("{green}Decompilation OK : '%s'\n", av[i]);
		free(env);
	}
	if (ac > 2)
		ft_printf("\n{cyan}------------------------------------------------\n");
	return (1);
}
