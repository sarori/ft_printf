/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cal_len.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sapark <sapark@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/31 02:16:49 by sapark            #+#    #+#             */
/*   Updated: 2019/08/31 02:27:22 by sapark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

u_int64_t	cnt_flen(t_pf *pf, u_int64_t num)
{
	u_int64_t	size;
	u_int64_t	len;

	size = 0;
	size = ft_digit_base_u(num, 10) + 1;
	size += pf->set.dot == 0 ? 6 : pf->set.precision;
	if (pf->set.sign)
		size++;
	else if (pf->set.plus)
		size++;
	else if (pf->set.space)
		size++;
	len = pf->set.width > (int)size ? pf->set.width : (int)size;
	if (!pf->set.hash && pf->set.dot && !pf->set.precision)
		len--;
	return (len);
}
