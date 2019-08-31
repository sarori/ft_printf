/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sapark <sapark@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/31 02:12:32 by sapark            #+#    #+#             */
/*   Updated: 2019/08/31 02:24:09 by sapark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	flag_setting(char *input, int *i, t_pf *pf)
{
	while (input[*i] == '-' || input[*i] == '+' || input[*i] == ' '
		|| input[*i] == '#' || input[*i] == '0')
	{
		if (input[*i] == '-')
			pf->set.minus = 1;
		else if (input[*i] == '+')
			pf->set.plus = 1;
		else if (input[*i] == ' ')
			pf->set.space = 1;
		else if (input[*i] == '#')
			pf->set.hash = 1;
		else if (input[*i] == '0')
			pf->set.zero = 1;
		*i += 1;
	}
}

void	width_setting(char *input, int *i, t_pf *pf)
{
	if (input[*i] >= '1' && input[*i] <= '9')
	{
		while (input[*i] >= '0' && input[*i] <= '9')
		{
			pf->set.width = pf->set.width * 10 + (input[*i] - '0');
			*i += 1;
		}
	}
}

void	precision_setting(char *input, int *i, t_pf *pf)
{
	pf->set.dot = 1;
	*i += 1;
	while (input[*i] >= '0' && input[*i] <= '9')
	{
		pf->set.precision = pf->set.precision * 10 + (input[*i] - '0');
		*i += 1;
	}
}

void	length_setting(char *input, int *i, t_pf *pf)
{
	if (input[*i] == 'l')
	{
		if (input[*i + 1] && input[*i + 1] == 'l')
		{
			pf->set.length_ll = 1;
			*i += 1;
		}
		else
			pf->set.length_l = 1;
		*i += 1;
	}
	else if (input[*i] == 'h')
	{
		if (input[*i + 1] && input[*i + 1] == 'h')
		{
			pf->set.length_hh = 1;
			*i += 1;
		}
		else
			pf->set.length_h = 1;
		*i += 1;
	}
	else if (input[*i] == 'L')
	{
		pf->set.length_L = 1;
		*i += 1;
	}
}
