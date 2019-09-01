/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sapark <sapark@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/31 19:11:16 by sapark            #+#    #+#             */
/*   Updated: 2019/08/31 19:24:41 by sapark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_color	g_color[] =
{
	{"{red}", "\033[0;31m"},
	{"{green}", "\033[0;32m"},
	{"{yellow}", "\033[0;33m"},
	{"{blue}", "\033[0;34m"},
	{"{magenta}", "\033[0;35m"},
	{"{cyan}", "\033[0;36m"},
	{"{eoc}", "\033[0m"},
	{NULL, NULL},
};

void	ft_color(char *s, int *i, t_pf *pf)
{
	int		idx;
	char	color[4096];

	idx = 0;
	while (s[*i] != '}' && s[*i] != '\0')
	{
		color[idx++] = s[(*i)++];
		if (s[*i] == '}')
			color[idx++] = '}';
	}
	color[idx] = '\0';
	idx = -1;
	while (ft_strlen(color) < 11 && g_color[++idx].color)
	{
		if (ft_strcmp(color, g_color[idx].color) == 0)
		{
			ft_strjoinfree(pf->res, g_color[idx].code, 0);
			*i += 1;
			return ;
		}
	}
	ft_strjoinfree(pf->res, "\033[0m", 1);
	ft_strjoinfree(pf->res, color, 1);
	s[*i] != '\0' ? (*i += 1) : 0;
}