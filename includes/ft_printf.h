/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sapark <sapark@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/31 02:40:03 by sapark            #+#    #+#             */
/*   Updated: 2019/08/31 19:30:39 by sapark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "libft.h"
# include <stdlib.h>
# include <stdarg.h>
//
#include <stdio.h>
//
#define SPECIFIER "cspdiouxXf%b"
typedef struct		s_flag_lst
{
	int				plus;
	int				minus;
	int				space;
	int				hash;
	int				zero;
	int				width;
	int				dot;
	int				precision;
	int				length_l;
	int				length_ll;
	int				length_h;
	int				length_hh;
	int				length_large;
	int				sign;
	int				per;
}					t_flag_lst;

typedef struct		s_typedt
{
	char			sp;
	void			(*f)();
}					t_typedt;

typedef struct		s_res
{
	char			*res;
	struct s_res	*next;
}					t_res;

typedef struct		s_color
{
	char			*color;
	char			*code;
}					t_color;

typedef struct		s_pf
{
	t_flag_lst		set;
	t_res			*head;
	char			*res;
	int				minus;
}					t_pf;

int					ft_printf(char *str, ...);
int					specifier(char *input, int *point, va_list *ap);
void				*ft_memalloc_chr(size_t size, char c);
int					setting(char *input, int *point, va_list *ap, t_pf *pf);
void				type_c(va_list *ap, t_pf *pf);
void				type_s(va_list *ap, t_pf *pf);
void				type_p(va_list *ap, t_pf *pf);
void				type_d(va_list *ap, t_pf *pf);
void				type_i(va_list *ap, t_pf *pf);
void				type_o(va_list *ap, t_pf *pf);
void				type_u(va_list *ap, t_pf *pf);
void				type_x(va_list *ap, t_pf *pf);
void				type_largex(va_list *ap, t_pf *pf);
void				type_f(va_list *ap, t_pf *pf);
void				type_per(va_list *ap, t_pf *pf);
void				type_b(va_list *ap, t_pf *pf);
int64_t				get_arg_di(va_list *ap, t_pf *pf);
u_int64_t			get_arg_uoxx(va_list *ap, t_pf *pf);
long double			get_arg_f(va_list *ap, t_pf *pf);
void				flag_setting(char *input, int *i, t_pf *pf);
void				width_setting(char *input, int *i, t_pf *pf);
void				precision_setting(char *input, int *i, t_pf *pf);
void				length_setting(char *input, int *i, t_pf *pf);
int					ft_digit_base(int n, int base);
int					ft_digit_base_u(unsigned long long n,
									unsigned long long base);
char				*ft_itoa_base(long long value, int base);
char				*ft_itoa_base_u(unsigned long long value,
									unsigned long long base);
char				*ft_itoa_bu(char *res, unsigned long long value,
								unsigned long long base);
char				*prec_handle(t_pf *pf, char *res, char *str);
char				*width_handle(t_pf *pf, char *res, char *str);
char				*element_join(char *res, char const *s1, char const *s2);
char				*ft_elem(char *res, char *str, int start, int size);
int					cal_len(t_pf *pf, u_int64_t num, int base);
char				*ft_str_toupper(char *str);
char				*di_minus_handle(t_pf *pf, char *res, char *tmp);
char				*di_handle(t_pf *pf, char *res, char *tmp);
u_int64_t			cnt_flen(t_pf *pf, u_int64_t num);
char				*f_minus_handle(t_pf *pf, char *res, long double num);
u_int64_t			cvt_num(t_pf *pf, long double num);
void				flaghandle(t_pf *pf, char *res);
char				*f_handle(t_pf *pf, char *res, long double num);
char				*ft_scjoin(char *s1, char c, int mfree);
char				*ft_strjoinfree(char *s1, char *s2, int mfree);
char				*o_minus_handle(t_pf *pf, char *res, char *tmp);
char				*ou_handle(t_pf *pf, char *res, char *tmp);
char				*di_zerohandle(t_pf *pf, char *res, int len);
char 				*f_zero_handle(t_pf *pf, char *res, int start, int size);
void				insertnode(t_pf *pf, char *res);
u_int64_t			zero_len(t_pf *pf, u_int64_t num);
char				*c_zerohandle(t_pf *pf, char *res, int len);
char				*p_handle(t_pf *pf, char *res, char *tmp, int len);
char				*di_helper(t_pf *pf, char *res, int len);
char				*di_helper2(t_pf *pf, char *res, char *tmp);
int					cal_helper(t_pf *pf, u_int64_t num, int max, int base);
char				*o_zero(t_pf *pf, int len);
char				*x_handle(t_pf *pf, char *res, char *tmp);
void				ft_color(char *s, int *i, t_pf *pf);
char				*x_helper(t_pf *pf, char *res, char *tmp);
#endif