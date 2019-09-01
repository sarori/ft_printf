/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_di.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sapark <sapark@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/31 16:24:42 by sapark            #+#    #+#             */
/*   Updated: 2019/08/31 16:26:13 by sapark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void			type_d(va_list *ap, t_pf *pf)
{
	int64_t	i;
	int		len;
	char	*res;
	char	*tmp;

	i = get_arg_di(ap, pf);
	pf->set.sign = i < 0 ? 1 : 0;
	len = cal_len(pf, i >= 0 ? i : i * -1, 10);
	tmp = ft_itoa_base_u(i >= 0 ? i : i * -1, 10);
	res = NULL;
	if (i == 0)
		res = di_zerohandle(pf, res, len);
	else
	{
		res = ft_memalloc_chr(len, ' ');
		res[len] = '\0';
		if (pf->set.minus)
			res = di_minus_handle(pf, res, tmp);
		else
			res = di_handle(pf, res, tmp);
	}
	insertnode(pf, res);
	pf->res = ft_strjoinfree(pf->res, res, 1);
	free(res);
}

void			type_i(va_list *ap, t_pf *pf)
{
	int64_t	i;
	int		len;
	char	*res;
	char	*tmp;

	i = get_arg_di(ap, pf);
	pf->set.sign = i < 0 ? 1 : 0;
	len = cal_len(pf, i >= 0 ? i : i * -1, 10);
	res = NULL;
	if (i == 0)
		res = di_zerohandle(pf, res, len);
	else
	{
		res = ft_memalloc_chr(len, ' ');
		res[len] = '\0';
		tmp = ft_itoa_base_u(i >= 0 ? i : i * -1, 10);
		if (pf->set.minus)
			res = di_minus_handle(pf, res, tmp);
		else
			res = di_handle(pf, res, tmp);
	}
	insertnode(pf, res);
	pf->res = ft_strjoinfree(pf->res, res, 1);
	free(res);
}
