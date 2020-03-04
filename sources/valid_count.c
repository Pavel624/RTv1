/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_count.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsatterf <rsatterf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 13:29:38 by rsatterf          #+#    #+#             */
/*   Updated: 2020/03/03 13:30:16 by rsatterf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	init_schet(t_rtv *rtv)
{
	rtv->l = 0;
	rtv->k = 0;
	rtv->e = 0;
	rtv->j = 0;
}

void	help_valid_count2(t_rtv *rtv)
{
	rtv->k++;
	rtv->l++;
}

void	help_valid_count(t_rtv *rtv)
{
	rtv->j++;
	rtv->l++;
}

int		valid_count(char *str, t_rtv *rtv)
{
	init_schet(rtv);
	while (str[rtv->l] != '\0')
	{
		if (str[rtv->l] == '-')
			rtv->l++;
		else if (str[rtv->l] >= 48 && str[rtv->l] <= 57)
		{
			rtv->e++;
			while (str[rtv->l] >= 48 && str[rtv->l] <= 57
			&& str[rtv->l] != '\0')
				rtv->l++;
		}
		else if (str[rtv->l] == ' ')
			help_valid_count(rtv);
		else if (str[rtv->l] == ')')
			help_valid_count2(rtv);
		else
			return (-1);
	}
	if ((rtv->j != 2) || (rtv->k != 1) || (rtv->e != 3))
		return (-1);
	return (0);
}

int		valid_count2(char *str)
{
	int i;
	int k;

	i = 0;
	k = 0;
	while (str[i] != '\0')
	{
		if ((str[i] >= 48 && str[i] <= 57) || (str[i] == '-'))
			i++;
		else if (str[i] == ')')
		{
			k++;
			i++;
		}
		else
			return (-1);
	}
	if (k != 1)
		return (-1);
	return (0);
}
