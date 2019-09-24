/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcopyuntil.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sskinner <sskinner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/27 13:56:06 by sskinner          #+#    #+#             */
/*   Updated: 2019/04/27 14:09:24 by sskinner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcopyuntil(char *str, int c)
{
	char	*tmp;
	int		i;

	if (!str)
		return (NULL);
	i = 0;
	if (!(tmp = ft_strnew(ft_strlen(str) + 1)))
		return (NULL);
	while (str[i] != (unsigned char)c)
	{
		tmp[i] = str[i];
		i++;
	}
	tmp[i] = '\0';
	return (tmp);
}
