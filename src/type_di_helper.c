/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_di_helper.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sapark <sapark@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/31 16:24:50 by sapark            #+#    #+#             */
/*   Updated: 2019/09/04 02:14:00 by sapark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char			*di_minus_handle(t_pf *pf, char *res, char *tmp)
{
	int		start;
	int		size;

	start = 0;
	if (res)
	{
		if (pf->set.sign)
			ft_elem(res, "-", start++, 1);
		else if (!pf->set.sign && pf->set.space)
			ft_elem(res, " ", start++, 1);
		else if (!pf->set.sign && pf->set.plus)
			ft_elem(res, "+", start++, 1);
	}
	if (pf->set.precision > (int)ft_strlen(tmp))
	{
		size = pf->set.precision - (int)ft_strlen(tmp);
		while (size--)
			res[start++] = '0';
	}
	size = (int)ft_strlen(res) - (int)ft_strlen(tmp) - start;
	ft_elem(res, tmp, start, (int)ft_strlen(tmp));
	return (res);
}

char			*di_helper2(t_pf *pf, char *res, char *tmp)
{
	int	start;
	int	size;

	size = (int)ft_strlen(res) - ft_strlen(tmp);
	start = (int)(ft_strlen(res) - ft_strlen(tmp)) - 1;
	if (pf->set.precision > (int)ft_strlen(tmp))
	{
		size = pf->set.precision - (int)ft_strlen(tmp);
		while (size--)
			res[start--] = '0';
	}
	if (!pf->set.sign)
	{
		if (pf->set.plus)
			ft_elem(res, "+", start, 1);
		else if (pf->set.space)
			ft_elem(res, " ", start, 1);
	}
	else
		ft_elem(res, "-", start, 1);
	return (res);
}

char			*di_handle(t_pf *pf, char *res, char *tmp)
{
	int	start;
	int	size;

	size = (int)ft_strlen(res) - ft_strlen(tmp);
	start = (int)(ft_strlen(res) - ft_strlen(tmp)) - 1;
	if (pf->set.zero)
	{
		if (pf->set.precision > (int)ft_strlen(tmp))
			size = pf->set.precision - (int)ft_strlen(tmp);
		while (size--)
			res[start--] = '0';
		if (pf->set.space && !pf->set.sign)
			ft_elem(res, " ", 0, 1);
		else if (pf->set.plus && !pf->set.sign)
			ft_elem(res, "+", 0, 1);
		else if (pf->set.sign)
			ft_elem(res, "-", 0, 1);
	}
	else
		res = di_helper2(pf, res, tmp);
	ft_elem(res, tmp, (int)ft_strlen(res) -
			(int)ft_strlen(tmp), (int)ft_strlen(tmp));
	return (res);
}

char			*di_helper(t_pf *pf, char *res, int len)
{
	int		start;
	int		size;

	start = 0;
	size = 0;
	if (pf->set.zero || pf->set.precision > 0)
	{
		size = pf->set.precision > 0 ? pf->set.precision : len - 1;
		while (size--)
		{
			res[len - 1] = '0';
			len--;
		}
	}
	if (pf->set.width <= 1)
		len = 1 + pf->set.plus;
	else
		len = pf->set.width;
	if (pf->set.plus)
		res = ft_elem(res, "+", start++, 1);
	if (!pf->set.dot)
		res = ft_elem(res, "0", start++, 1);
	return (res);
}

char			*di_zerohandle(t_pf *pf, char *res, int len)
{
	int		start;
	int		size;

	start = 0;
	size = 0;
	len = cal_len(pf, 0, 10);
	if (pf->set.dot && !pf->set.precision && !pf->set.width)
	{
		len = 0;
		res = ft_memalloc_chr(len, ' ');
		res[len] = '\0';
		return (res);
	}

	else if (pf->set.hash && !pf->set.precision
			&& !pf->set.width && !pf->set.precision)
		len = 1;
	res = ft_memalloc_chr(len, ' ');
	res[len] = '\0';
	res = di_helper(pf, res, len);
	return (res);
}
