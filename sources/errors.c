/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsatterf <rsatterf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 12:51:37 by rsatterf          #+#    #+#             */
/*   Updated: 2020/03/03 12:54:18 by rsatterf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void			valid(t_rtv *rtv)
{
	if ((valid1(rtv) != 0))
	{
		free(rtv);
		ft_error(OPEN_FILE_ERR);
	}
	else if ((valid2(rtv) != 0))
	{
		free(rtv);
		ft_error(INVALID_SYMBOLS);
	}
	render2(rtv);
	if (count_items(rtv) != 0)
	{
		free(rtv);
		ft_strdel(rtv->scene);
		ft_error(CAM_OR_LIGHT_ERR);
	}
	malloc_structures(rtv);
	if (valid_objects(rtv) != 0)
	{
		free(rtv);
		ft_error(INVALID_OBJ);
	}
}

int				close_app(t_rtv *rtv)
{
	free(rtv);
	exit(0);
}

void			ft_error(int code)
{
	if (code == TOO_MANY_PARAMS)
		ft_putstr("Too many parameters\n");
	else if (code == USE_SCENE)
		ft_putstr("Use scene from scenes folder\n");
	else if (code == RTV_ERR)
		ft_putstr("Can't allocate enough memory for the structure\n");
	else if (code == MEM_ALLOC_ERR)
		ft_putstr("Memory allocation error!\n");
	else if (code == OPEN_FILE_ERR)
		ft_putstr("Can't open specified file\n");
	else if (code == INVALID_SYMBOLS)
		ft_putstr("Invalid symbols were found in the file\n");
	else if (code == CAM_OR_LIGHT_ERR)
		ft_putstr("No light or not one camera in the file\n");
	else if (code == INVALID_OBJ)
		ft_putstr("Invalid scene or content description\n");
	else
		ft_putstr("Something went wrong\n");
	exit(0);
}
