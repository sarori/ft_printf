/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sapark <sapark@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/31 02:38:44 by sapark            #+#    #+#             */
/*   Updated: 2019/08/31 03:06:16 by sapark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int			ft_printf(char *str, ...)
{
	int		i;
	int		cnt;

	va_list ap;
	t_pf *pf;
	pf = ft_memalloc(sizeof(t_pf));
	i = 0;
	cnt = 0;
	va_start(ap, str);
	while (str[i])
	{
		if (str[i] == '%')
			setting(str, &i, &ap, pf);
		else
			pf->res = ft_scjoin(pf->res, str[i], 1);
		i++;
	}
	va_end(ap);
	ft_putstr(pf->res);
	return ((int)ft_strlen(pf->res) - pf->minus);
}

t_typedt	set_dt[] =
{
	{'c', type_c},
	{'s', type_s},
	{'p', type_p},
	{'d', type_d},
	{'i', type_i},
	{'o', type_o},
	{'u', type_u},
	{'x', type_x},
	{'X', type_X},
	{'f', type_f},
	{'%', type_per},
	{'b', type_b}
};

int			setting(char *input, int *i, va_list *ap, t_pf *pf)
{
	int	idx;

	idx = 0;
	*i += 1;
	pf->set = (t_flag_lst){0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	if (input[*i])
	{
		if (input[*i] == '-' || input[*i] == '+' || input[*i] == ' '
			|| input[*i] == '#' || input[*i] == '0')
			flag_setting(input, i, pf);
		if (input[*i] >= '1' && input[*i] <= '9')
			width_setting(input, i, pf);
		if (input[*i] == '.')
			precision_setting(input, i, pf);
		if (input[*i] == 'l' || input[*i] == 'h' || input[*i] == 'L')
			length_setting(input, i, pf);
		idx = ft_strchr_idx(SPECIFIER, input[*i]);
	}
	set_dt[idx].f(ap, pf);
	return (0);
	(void)ap;
}
