/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dasmc.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abassibe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/01 04:08:31 by abassibe          #+#    #+#             */
/*   Updated: 2018/02/01 05:48:24 by abassibe         ###   ########.fr       */
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
	tmp = ft_strjoin(tab[0], ".s");
	free(tab[0]);
	free(tab[1]);
	free(tab);
	return (tmp);
}

char	get_header(t_env *env)
{
	int		magic;

	magic = 0;
	magic |= ((env->str[0] & 0xff) << 24);
	magic |= ((env->str[1] & 0xff) << 16);
	magic |= ((env->str[2] & 0xff) <<  8);
	magic |= ((env->str[3] & 0xff));
	if (magic != 15369203)
	{
		env->error = ft_strdup("Bad magic number");
		return (0);
	}
	return (1);
}

char	start(t_env *env, const char *file_name)
{
	char	*champ;
	int		value;

	env->str = ft_strnew(4);
	if ((env->fd_bin = open(file_name, O_RDONLY)) == -1)
		return (0);
	champ = creat_bin(file_name);
	if ((env->fd_champ = open(champ, O_WRONLY | O_CREAT, 0777)) == -1)
		return (0);
	ft_strdel(&champ);
	if ((value = read(env->fd_bin, env->str, 4)) > 0)
		if (!get_header(env))
			return (0);
	if (value == -1)
	{
		perror("");
		return (0);
	}
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
			ft_printf("{red}An error occured with '%s'\n", av[i]);
		else
			ft_printf("{green}Decompilation OK : '%s'\n", av[i]);
		free(env);
	}
	if (ac > 2)
		ft_printf("\n{cyan}------------------------------------------------\n");
	return (1);
}
