/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_di.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sapark <sapark@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/31 02:53:58 by sapark            #+#    #+#             */
/*   Updated: 2019/08/31 13:38:04 by sapark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
long long		check_size_di(int n)
{
	int	size;

	size = 0;
	if (n == -2147483648)
		size = 11;
	else
		size = n < 0 ? ft_digit(n * -1) + 1 : ft_digit(n);
	return (size);
}

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

char			*di_handle(t_pf *pf, char *res, char *tmp)
{
	int	start;
	int	size;
	int	i;
	
	size = (int)ft_strlen(res) - ft_strlen(tmp);
	start = (int)(ft_strlen(res) - ft_strlen(tmp)) - 1;
	i = 0;
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
	{
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
	}
	ft_elem(res, tmp, (int)ft_strlen(res) - (int)ft_strlen(tmp) , (int)ft_strlen(tmp));
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
		len = 0;
	res = ft_memalloc_chr(len, ' ');
	res[len] = '\0';
	if (pf->set.zero && pf->set.precision > 0)
	{
		size = pf->set.precision;
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

void			type_d(va_list *ap, t_pf *pf)
{
	int64_t	i;
	int		len;
	char	*res;
	char	*tmp;

	i = get_arg_di(ap, pf);
	pf->set.sign= i < 0 ? 1 : 0;
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