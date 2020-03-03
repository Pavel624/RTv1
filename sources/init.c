/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsatterf <rsatterf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 12:57:33 by rsatterf          #+#    #+#             */
/*   Updated: 2020/03/03 13:01:07 by rsatterf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

char	*ft_strjoin_2(char *s1, char *s2)
{
	char	*snew;
	size_t	len;

	if (!s1 || !s2)
		return (NULL);
	len = ft_strlen(s1) + ft_strlen(s2);
	snew = (char *)malloc(sizeof(*snew) * (len + 1));
	if (!snew)
		return (NULL);
	ft_strcpy(snew, s1);
	ft_strcat(snew, s2);
	ft_strdel(&s1);
	return (snew);
}

void	render2(t_rtv *rtv)
{
	char	*line;
	char	*str;

	line = NULL;
	str = NULL;
	rtv->buf = ft_strnew(1);
	rtv->fd = open(rtv->name, O_RDONLY);
	while (get_next_line(rtv->fd, &line) > 0)
	{
		str = ft_strjoin(line, "\n");
		rtv->buf = ft_strjoin_2(rtv->buf, str);
		ft_strdel(&str);
		ft_strdel(&line);
	}
	rtv->scene = ft_strsplit(rtv->buf, '\n');
	ft_strdel(&line);
	ft_strdel(&str);
	ft_strdel(&rtv->buf);
}

void	init_array(t_rtv *rtv)
{
	rtv->nbr[CAM] = 0;
	rtv->nbr[LIGHT] = 0;
	rtv->nbr[SPHERE] = 0;
	rtv->nbr[PLANE] = 0;
	rtv->nbr[CYLINDER] = 0;
	rtv->nbr[CONE] = 0;
	rtv->index[CAM] = 0;
	rtv->index[LIGHT] = 0;
	rtv->index[SPHERE] = 0;
	rtv->index[PLANE] = 0;
	rtv->index[CYLINDER] = 0;
	rtv->index[CONE] = 0;
}

int		count_items(t_rtv *rtv)
{
	int i;

	i = 0;
	init_array(rtv);
	while (rtv->scene[i])
	{
		if (ft_strcmp(rtv->scene[i], "camera\0") == 0)
			rtv->nbr[CAM]++;
		else if (ft_strcmp(rtv->scene[i], "light\0") == 0)
			rtv->nbr[LIGHT]++;
		else if (ft_strcmp(rtv->scene[i], "sphere\0") == 0)
			rtv->nbr[SPHERE]++;
		else if (ft_strcmp(rtv->scene[i], "plane\0") == 0)
			rtv->nbr[PLANE]++;
		else if (ft_strcmp(rtv->scene[i], "cylinder\0") == 0)
			rtv->nbr[CYLINDER]++;
		else if (ft_strcmp(rtv->scene[i], "cone\0") == 0)
			rtv->nbr[CONE]++;
		i++;
	}
	if ((rtv->nbr[CAM] != 1) || (rtv->nbr[LIGHT] == 0))
		return (-1);
	return (0);
}

void	malloc_structures(t_rtv *rtv)
{
	if (!(rtv->cam = (t_cam*)malloc(rtv->nbr[CAM] * sizeof(t_cam))) ||
	!(rtv->light = (t_light*)malloc(rtv->nbr[LIGHT] * sizeof(t_light))) ||
	!(rtv->sphere = (t_sphere*)malloc(rtv->nbr[SPHERE] * sizeof(t_sphere))) ||
	!(rtv->plane = (t_plane*)malloc(rtv->nbr[PLANE] * sizeof(t_plane))) ||
	!(rtv->cylinder = (t_cylinder*)malloc(rtv->nbr[CYLINDER] *
		sizeof(t_cylinder)))
	|| !(rtv->cone = (t_cone*)malloc(rtv->nbr[CONE] * sizeof(t_cone))))
	{
		free(rtv);
		ft_error(MEM_ALLOC_ERR);
	}
}
