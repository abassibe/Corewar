/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcluchet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/07 01:27:32 by pcluchet          #+#    #+#             */
/*   Updated: 2016/11/09 14:15:25 by pcluchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isascii(int c)
{
	char k;

	k = c;
	if (k == c && c >= 0 && k <= 127)
		return (1);
	return (0);
}
