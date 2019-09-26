/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbethany <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/26 20:42:17 by nbethany          #+#    #+#             */
/*   Updated: 2019/09/26 20:42:18 by nbethany         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int 	key_release(int key, t_rtv *rtv)
{
	if (key == KEY_ESC)
	{
		mlx_destroy_image(rtv->mlx, rtv->window);
		free(rtv);
		exit(EXIT_SUCCESS);
	}
	return (1);
}