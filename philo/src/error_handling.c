/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaadeh <asaadeh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 18:06:20 by asaadeh           #+#    #+#             */
/*   Updated: 2025/07/17 20:42:04 by asaadeh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isdigit(int s)
{
	if (s >= '0' && s <= '9')
	{
		return (1);
	}
	return (0);
}

int	ft_atoi(const char *nptr)
{
	char	*str;
	int		i;
	int		res;
	int		sign;

	sign = 1;
	i = 0;
	res = 0;
	str = (char *)nptr;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
		{
			sign = -sign;
		}
		i++;
	}
	while ((str[i] != '\0') && (str[i] >= '0' && str[i] <= '9'))
	{
		res = res * 10 + str[i] - '0';
		i++;
	}
	return (res * sign);
}

int	valid_arg(char **argv)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
		{
			if (argv[i][j] == '+')
				j++;
			if (!ft_isdigit(argv[i][j]))
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}
