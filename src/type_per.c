/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_per.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sapark <sapark@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/31 02:13:00 by sapark            #+#    #+#             */
/*   Updated: 2019/08/31 16:53:42 by sapark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	type_per(va_list *ap, t_pf *pf)
{
	char	per;
	char	*res;
	int		len;
	int		i;

	per = (char)va_arg(*ap, int);
	len = pf->set.width > 1 ? pf->set.width : 1;
	res = ft_memalloc_chr(len, ' ');
	i = 0;
	res[len] = '\0';
	if (pf->set.minus)
		res[i] = '%';
	else
	{
		if (pf->set.zero)
		{
			while (len - 1 > i)
				res[i++] = '0';
		}
		res[len - 1] = '%';
	}
	insertnode(pf, res);
	pf->res = ft_strjoinfree(pf->res, res, 1);
	free(res);
}

void	type_b(va_list *ap, t_pf *pf)
{
	u_int64_t	binary;
	char		*res;
	char		*tmp;
	int			start;
	int			len;
	
	binary = get_arg_uoxx(ap, pf);
	len = binary == 0 ? pf->set.width : cal_len(pf, binary, 2);
	tmp = ft_itoa_base_u(binary, 2);
	if (pf->set.precision > (int)ft_strlen(tmp) && pf->set.precision > len)
		len = pf->set.precision + pf->set.hash ?
			pf->set.precision + 2 : pf->set.precision;
	start = 0;
	res = ft_memalloc_chr(len, ' ');
	res[len] = '\0';
	if (binary == 0)
	{
		if (!pf->set.dot)
			res = ft_elem(res, "0", start, 1);
	}
	else
	{
		if (pf->set.minus)
		{
			if (pf->set.hash)
			{
				ft_elem(res, "0b", start, 2);
				ft_elem(res, tmp, start + 2, (int)ft_strlen(tmp));
			}
			else
				ft_elem(res, tmp, start, (int)ft_strlen(tmp));
		}
		else
		{
			start = len - (ft_digit_base_u(binary, 2));
			ft_elem(res, tmp, start, (int)ft_strlen(tmp));
			if (pf->set.zero || pf->set.precision > (int)ft_strlen(tmp))
			{
				while (start > 0)
				{
					res[start - 1] = '0';
					start--;
				}
				if (pf->set.hash)
					ft_elem(res, "0b", start, 2);
			}
			else
			{
				if (pf->set.hash && len > 1)
					ft_elem(res, "0b", start - 2, 2);
			}
		}
	}
	insertnode(pf, res);
	pf->res = ft_strjoinfree(pf->res, res, 1);
	free(res);
}
