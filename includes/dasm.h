/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dasm.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abassibe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/01 04:06:38 by abassibe          #+#    #+#             */
/*   Updated: 2018/02/02 05:31:19 by abassibe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DASM_H
# define DASM_H

# include "libft.h"
# include "op.h"
# include <fcntl.h>

typedef struct			s_env
{
	char				*str;
	int					fd_bin;
	int					fd_champ;
	char				*label[CHAMP_MAX_SIZE];
	int					champ_size;
	char				*champ_s;
	char				*error;
}						t_env;

char					get_header(t_env *env);
char					get_magic_number(t_env *env);
char					*creat_bin(const char *str);
void					clear_buff(char *str);
void					ft_error(const char *str, const int check);
#endif
