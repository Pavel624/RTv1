/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strreverse.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sskinner <sskinner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/06 13:40:42 by sskinner          #+#    #+#             */
/*   Updated: 2019/04/17 16:08:40 by sskinner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strreverse(const char *str)
{
	size_t	count;
	size_t	end;
	size_t	i;
	char	*reverse;

	i = 0;
	count = ft_strlen(str);
	if (!(reverse = ft_strnew(count)))
		return (NULL);
	end = count - 1;
	while (i < count)
	{
		reverse[i] = str[end];
		i++;
		end--;
	}
	reverse[i] = '\0';
	return (reverse);
}
