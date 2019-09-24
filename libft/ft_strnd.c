/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sskinner <sskinner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/30 17:23:59 by sskinner          #+#    #+#             */
/*   Updated: 2019/05/02 14:26:55 by sskinner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnd(const char *s1, const char *s2, size_t n, size_t i)
{
	size_t	j;

	j = 0;
	while (s1[i] && n > 0)
	{
		if (s1[i] == s2[j])
		{
			if (ft_strlen(s2) == 1)
				return ((char *)&s1[i - ft_strlen(s2) + 1]);
			j++;
			if ((j == ft_strlen(s2) - 1) &&
			(s1[i + 1] == s2[j]) && (n - 1) > 0)
				return ((char *)&s1[i - ft_strlen(s2) + 2]);
			if (s1[i + 1] != s2[j])
			{
				i = i - j + 1;
				n = n + j - 1;
				j = 0;
			}
		}
		i++;
		n--;
	}
	return (NULL);
}
