/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_ou.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sapark <sapark@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/31 02:12:53 by sapark            #+#    #+#             */
/*   Updated: 2019/08/31 13:28:15 by sapark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void			type_i(va_list *ap, t_pf *pf)
{
	int64_t	i;
	int		len;
	char	*res;
	char	*tmp;

	i = get_arg_di(ap, pf);
	pf->set.sign= i < 0 ? 1 : 0;
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

char			*o_minus_handle(t_pf *pf, char *res, char *tmp)
{
	int			start;
	int			size;
	
	start = 0;
	
	if (pf->set.precision > (int)ft_strlen(tmp))
	{
		size = pf->set.precision - (int)ft_strlen(tmp);
		while (size--)
			res[start++] = '0';
	}
	if (pf->set.hash)
	{
		ft_elem(res, "0", start, 1);
		ft_elem(res, tmp, start + 1, (int)ft_strlen(tmp));
	}
	else
		ft_elem(res, tmp, start, (int)ft_strlen(tmp));
	return (res);
}

char			*ou_handle(t_pf *pf, char *res, char *tmp)
{
	int	start;
	int	len;
	int size;

	len = (int)ft_strlen(res);
	start = len - ft_strlen(tmp);
	size = pf->set.precision - (int)ft_strlen(tmp);
	ft_elem(res, tmp, start, (int)ft_strlen(tmp));
	if (pf->set.hash)
		ft_elem(res, "0", start - 1, 1);
	if (pf->set.zero)
	{
		size = pf->set.width > (int)ft_strlen(tmp) ?
		pf->set.width - (int)ft_strlen(tmp) : size;
		while (size-- > 0)
			res[--start] = '0';
	}
	if (!pf->set.zero)
	{
		size = pf->set.precision > (int)ft_strlen(tmp) ?
		pf->set.precision - (int)ft_strlen(tmp) : size;
		while (size-- > 0)
			res[--start] = '0';
	}
	return (res);
}

void			type_o(va_list *ap, t_pf *pf)
{
	u_int64_t	octal;
	char		*res;
	char		*tmp;
	int			len;

	res = NULL;
	octal = get_arg_uoxX(ap, pf);
	len = octal == 0 ? 1 : cal_len(pf, octal, 8);
	if (octal == 0)
	{
		if (!pf->set.dot || pf->set.hash)
		{
			res = ft_memalloc_chr(len, ' ');
			res[len] = '\0';
			res = ft_elem(res, "0", 0, 1);
		}
		else
		res = di_zerohandle(pf, res, len);
	}
	else
	{
		res = ft_memalloc_chr(len, ' ');
		res[len] = '\0';
		tmp = ft_itoa_base_u(octal, 8);
		if (pf->set.minus)
			res = o_minus_handle(pf, res, tmp);
		else
			res = ou_handle(pf, res, tmp);
	}
	insertnode(pf, res);
	pf->res = ft_strjoinfree(pf->res, res, 1);
	free(res);
}

void			type_u(va_list *ap, t_pf *pf)
{
	u_int64_t	u;
	char		*res;
	char		*tmp;
	int			start;
	int			len;

	u = get_arg_uoxX(ap, pf);
	len = cal_len(pf, u, 10);
	start = 0;
	res = ft_memalloc_chr(len, ' ');
	if (pf->set.plus || pf->set.space)
		len -= 1;
	res[len] = '\0';
	if (u == 0)
		res = di_zerohandle(pf, res, len);
	else
	{
		tmp = ft_itoa_base_u(u, 10);
		if (pf->set.minus)
			ft_elem(res, tmp, start, (int)ft_strlen(tmp));
		else
			res = ou_handle(pf, res, tmp);
	}
	insertnode(pf, res);
	pf->res = ft_strjoinfree(pf->res, res, 1);
	free(res);
}
