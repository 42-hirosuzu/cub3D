/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_xbase.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hirosuzu <hirosuzu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 10:02:02 by hirosuzu          #+#    #+#             */
/*   Updated: 2023/10/14 08:51:29 by hirosuzu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"printf.h"

void	ft_xbase(unsigned long long n, int base, int istoupper, int *len)
{
	int	mod;

	if (n >= (unsigned long long)base)
		ft_xbase(n / base, base, istoupper, len);
	mod = n % base;
	if (mod < 10)
		pf_putchar_fd((mod + '0'), 1);
	else if (mod >= 10 && istoupper)
		pf_putchar_fd((mod + 'A' - 10), 1);
	else if (mod >= 10)
		pf_putchar_fd((mod + 'a' - 10), 1);
	*len += 1;
}
