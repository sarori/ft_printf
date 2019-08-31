/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_xlxf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sapark <sapark@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/31 02:13:07 by sapark            #+#    #+#             */
/*   Updated: 2019/08/31 14:01:37 by sapark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	type_x(va_list *ap, t_pf *pf)
{
	u_int64_t	hex;
	char		*res;
	char		*tmp;
	int			start;
	int			len;
	int			size;

	hex = get_arg_uoxX(ap, pf);
	len = hex == 0 ? pf->set.width : cal_len(pf, hex, 16);
	tmp = ft_itoa_base_u(hex, 16);
	if (pf->set.precision > (int)ft_strlen(tmp) && pf->set.precision > len)
		len = pf->set.precision + pf->set.hash ? pf->set.precision + 2 : pf->set.precision; 
	start = 0;
	size = (int)ft_strlen(tmp) - start;
	res = ft_memalloc_chr(len, ' ');
	res[len] = '\0';
	if (hex == 0)
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
				ft_elem(res, "0x", start, 2);
				ft_elem(res, tmp, start + 2, (int)ft_strlen(tmp));
			}
			else
				ft_elem(res, tmp, start, (int)ft_strlen(tmp));
		}
		else
		{
			start = len - (ft_digit_base_u(hex, 16));
			ft_elem(res, tmp, start, (int)ft_strlen(tmp));
			if (pf->set.hash)
				ft_elem(res, "0x", (int)(ft_strlen(res) -ft_strlen(tmp) - 2), 2);
			if (pf->set.zero || (pf->set.precision > (int)ft_strlen(tmp) &&pf->set.precision >= pf->set.width))
			{
				while (start > 0)
				{
					res[start - 1] = '0';
					start--;
				}
				if (pf->set.hash)
					ft_elem(res, "0x", 0, 2);
			}
			
		}
	}
	insertnode(pf, res);
	pf->res = ft_strjoinfree(pf->res, res, 1);
	free(res);
}

char	*ft_str_toupper(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] >= 'a' && str[i] <= 'z')
			str[i] = str[i] - 32;
		i++;
	}
	return (str);
}

void	type_X(va_list *ap, t_pf *pf)
{
	u_int64_t	hex_l;
	char		*res;
	char		*tmp;
	int			start;
	int			len;

	hex_l = get_arg_uoxX(ap, pf);
	len = hex_l == 0 ? pf->set.width : cal_len(pf, hex_l, 16);
	start = 0;
	res = ft_memalloc_chr(len, ' ');
	res[len] = '\0';
	tmp = ft_itoa_base_u(hex_l, 16);
	tmp = ft_str_toupper(tmp);
	if (hex_l == 0)
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
				ft_elem(res, "0X", start, 2);
				ft_elem(res, tmp, start + 2, (int)ft_strlen(tmp));
			}
			else
				ft_elem(res, tmp, start, (int)ft_strlen(tmp));
		}
		else
		{
			start = len - (ft_digit_base_u(hex_l, 16));
			ft_elem(res, tmp, start, (int)ft_strlen(tmp));
			if (pf->set.hash)
			{
				ft_elem(res, "0X", start - 2, 2);
				start -= 2;
			}
			if (pf->set.zero || (pf->set.precision > (int)ft_strlen(tmp) &&pf->set.precision >= pf->set.width))
			{
				while (start > 0)
				{
					res[start - 1] = '0';
					start--;
				}	
			}
		}
	}
	insertnode(pf, res);
	pf->res = ft_strjoinfree(pf->res, res, 1);
	free(res);
}

