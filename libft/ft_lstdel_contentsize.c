/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel_contentsize.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sskinner <sskinner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/18 17:44:36 by sskinner          #+#    #+#             */
/*   Updated: 2019/05/19 18:22:03 by sskinner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_lstdel_contentsize(t_list **alst, size_t size)
{
	t_list	*ptr;
	t_list	*buf;

	ptr = *alst;
	if (*alst && (*alst)->content_size != size)
	{
		while (ptr && ptr->next->content_size != size)
			ptr = ptr->next;
		if (ptr)
		{
			buf = ptr->next;
			ptr->next = ptr->next->next;
			free(buf->content);
			free(buf);
		}
		return (ptr) ? (0) : (-1);
	}
	else if ((*alst)->content_size == size)
	{
		buf = *alst;
		*alst = (*alst)->next;
		free(buf->content);
		free(buf);
	}
	return (*alst) ? (0) : (-1);
}
