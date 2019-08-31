/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_csp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sapark <sapark@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/31 02:12:12 by sapark            #+#    #+#             */
/*   Updated: 2019/08/31 03:05:42 by sapark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	type_c(va_list *ap, t_pf *pf)
{
	char	*res;
	int		i;
	int		len;
	int		start;

	i = (char)va_arg(*ap, int);
	len = pf->set.width >= 1 ? pf->set.width : 1;
	start = pf->set.width > 1 ? pf->set.width - 1 : 1;
	if (i == 0)
		len += 1;
	res = ft_memalloc_chr(len, ' ');
	res[len] = '\0';
	if (i == 0)
	{
		if (pf->set.minus || pf->set.precision)
		{
			if (i == 0)
			{
				res[0] = '^';
				res[1] = '@';
				pf->minus += 1;
			}
			else
				res[0] = i;
		}
		else
		{
			if (i == 0)
			{
				res[len - 2] = '^';
				res[len - 1] = '@';
				pf->minus += 1;
			}
			else
				res[start - 1] = i;
		}
	}
	else
	{
		if (pf->set.minus)
			res[0] = i;
		else
			res[len - 1] = i;
	}
	insertnode(pf, res);
	pf->res = ft_strjoinfree(pf->res, res, 1);
	free(res);
}

char	*width_handle(t_pf *pf, char *res, char *str)
{
	int	size;
	int	i;

	i = 0;
	size = pf->set.precision >= (int)ft_strlen(str) ?
			ft_strlen(str) : pf->set.precision;
	while (size-- > 0)
	{
		res[i] = str[i];
		i++;
	}
	res[i] = '\0';
	return (res);
}

char	*prec_handle(t_pf *pf, char *res, char *str)
{
	int	i;
	int	start;
	int	size;

	i = 0;
	if (pf->set.dot)
		size = pf->set.precision >= (int)ft_strlen(str) ?
			(int)ft_strlen(str) : pf->set.precision;
	else
		size = ft_strlen(str);
	if (pf->set.minus)
	{
		while (size-- > 0)
		{
			res[i] = str[i];
			i++;
		}
	}
	else
	{
		start = ft_strlen(res) - size;
		while (size-- > 0)
			res[start++] = str[i++];
	}
	return (res);
}

void	type_s(va_list *ap, t_pf *pf)
{
	char	*res;
	char	*str;
	int		len;

	len = cal_len(pf, ft_strlen(str), 10);
	str = va_arg(*ap, char *);
	if (!str)
		pf->res = ft_strjoinfree(pf->res, "(null)", 1);
	else
	{
		len = pf->set.width > (int)ft_strlen(str) ? pf->set.width : (int)ft_strlen(str);
		res = ft_memalloc_chr(len, ' ');
		res[len] = '\0';
		if (!pf->set.width && !pf->set.dot)
			res = ft_strcpy(res, str);
		else
		{
			if (pf->set.dot && !pf->set.width)
				res = width_handle(pf, res, str);
			else
				res = prec_handle(pf, res, str);
		}
		insertnode(pf, res);
		pf->res = ft_strjoinfree(pf->res, res, 1);
		free(res);
	}
}

void	type_p(va_list *ap, t_pf *pf)
{
	char	*res;
	char	*tmp;
	void	*ptr;
	int		len;
	int		start;
	int		size;

	ptr = va_arg(*ap, void *);
	start = 0;
	size = 0;
	len = cal_len(pf, (unsigned long long)ptr, 16) + 2;
	res = NULL;
	if ((unsigned long long)ptr == 0)
	{
		if (pf->set.dot)
			len--;
		res = ft_memalloc_chr(len, ' ');
		res[len] = '\0';
		ft_elem(res, "0x", start, 2);
		if (!pf->set.dot)
			ft_elem(res, "0", start + 2, 2);
	}
	else
	{
		res = ft_memalloc_chr(len, ' ');
		res[len] = '\0';
		tmp = ft_itoa_base_u((unsigned long long)ptr, 16);
		if (pf->set.minus)
		{
			res = di_minus_handle(pf, res, tmp);
			ft_elem(res, "0x", 0, 2);
		}
		else
		{
			res = di_handle(pf, res, tmp);
			ft_elem(res, "0x", 0, 2);
		}
	}
	insertnode(pf, res);
	pf->res = ft_strjoinfree(pf->res, res, 1);
	free(res);
}
