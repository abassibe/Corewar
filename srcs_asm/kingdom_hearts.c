/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kingdom_hearts.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abassibe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/23 02:58:23 by abassibe          #+#    #+#             */
/*   Updated: 2018/01/26 03:49:49 by abassibe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

void	print_op(t_env *env, const char *str)
{
	int			i;
	t_label		*tmp;

	i = -1;
	tmp = env->label;
	while (++i < 16)
	{
		while (tmp)
		{
			if (ft_strnstr(str, tmp->label_name, ft_strlen(tmp->label_name)))
				str += ft_strlen(tmp->label_name) + 1;
			tmp = tmp->next;
			while (*str && *str < 33)
				str++;
		}
		if (ft_strnstr(str, env->op[i], ft_strlen(env->op[i])))
			env->opf[i](env, str);
		tmp = env->label;
	}
}

void	print_core(t_env *env, const char *str)
{
	int		i;

	i = 0;
	alloc_op_functions(env);
	while (*str < 33)
		str++;
	if (i == 2)
		;
//	if (is_label(env, str, i))
//		fonction_du_label();
	else
		print_op(env, str);
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
