/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lnum.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaadeh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 16:34:19 by asaadeh           #+#    #+#             */
/*   Updated: 2024/09/09 16:34:21 by asaadeh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	i_len(int n)
{
	int	len;

	len = 0;
	if (n == 0)
		return (1);
	if (n <= 0)
	{
		len++;
	}
	while (n)
	{
		n /= 10;
		len++;
	}
	return (len);
}

int	ft_lnum(int a)
{
	ft_putnbr_fd(a, 1);
	return (i_len(a));
}
