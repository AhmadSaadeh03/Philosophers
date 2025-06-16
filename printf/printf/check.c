/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaadeh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 18:31:14 by asaadeh           #+#    #+#             */
/*   Updated: 2024/09/08 18:31:23 by asaadeh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_hexlower(size_t n)
{
	char	*lower;
	int		count;

	lower = "0123456789abcdef";
	count = 0;
	if (n / 16 != 0)
	{
		count += ft_hexlower(n / 16);
	}
	ft_putchar_fd(lower[n % 16], 1);
	return (count + 1);
}

static int	ft_hexupper(size_t n)
{
	char	*upper;
	int		count;

	upper = "0123456789ABCDEF";
	count = 0;
	if (n / 16 != 0)
	{
		count += ft_hexupper(n / 16);
	}
	ft_putchar_fd(upper[n % 16], 1);
	return (count + 1);
}

static int	ft_unsigned_putnbr_fd(unsigned int n, int fd)
{
	unsigned int	a;
	int				count;

	a = n;
	count = 0;
	if (a / 10 != 0)
	{
		count += ft_unsigned_putnbr_fd(a / 10, fd);
	}
	ft_putchar_fd(a % 10 + '0', fd);
	return (count + 1);
}

static int	ft_pointer(size_t a)
{
	int	count;

	count = 0;
	if (a)
	{
		ft_putchar_fd('0', 1);
		ft_putchar_fd('x', 1);
		count = ft_hexlower(a);
		return (count + 2);
	}
	else
		return (write(1, "(nil)", 5));
}

int	check(char find, va_list args)
{
	if (find == 'c')
		return (ft_putchar_fd(va_arg(args, int), 1));
	else if (find == 's')
		return (ft_putstr_fd(va_arg(args, char *), 1));
	else if (find == 'd' || find == 'i')
		return (ft_lnum(va_arg(args, int)));
	else if (find == 'u')
		return (ft_unsigned_putnbr_fd(va_arg(args, unsigned int), 1));
	else if (find == 'x')
		return (ft_hexlower(va_arg(args, unsigned int)));
	else if (find == 'X')
		return (ft_hexupper(va_arg(args, unsigned int)));
	else if (find == '%')
	{
		return (write(1, "%", 1));
	}
	else if (find == 'p')
		return (ft_pointer(va_arg(args, size_t)));
	return (0);
}
