/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dasm.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abassibe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/01 04:06:38 by abassibe          #+#    #+#             */
/*   Updated: 2018/02/01 05:48:26 by abassibe         ###   ########.fr       */
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
	char				*error;
}						t_env;

#endif
