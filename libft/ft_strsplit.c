/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abassibe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/24 18:11:09 by abassibe          #+#    #+#             */
/*   Updated: 2017/11/30 02:23:25 by abassibe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

static int	c_word(char const *s, char c)
{
	int		p;
	int		k;

	p = 0;
	k = 0;
	while (s[p])
	{
		while (s[p] == c)
			p++;
		while (s[p] && s[p] != c)
		{
			p++;
			if (s[p] == c || !s[p])
				k++;
		}
	}
	return (k);
}

char		**ft_strsplit(char const *s, char c)
{
	char	**tb;
	int		k;
	int		p;
	int		f;

	k = 0;
	p = 0;
	f = 0;
	if (s == NULL ||
			!(tb = (char **)ft_memalloc(sizeof(char *) * c_word(s, c) + 1)))
		return (NULL);
	while (s[k] && p < c_word(s, c))
	{
		while (s[k] && s[k] == c)
			k++;
		f = k;
		while (s[f] && s[f] != c)
			f++;
		if (p <= c_word(s, c))
			tb[p] = ft_strsub(s, k, f - k);
		k = f;
		p++;
	}
	return (tb);
}
