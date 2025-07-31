/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfilipe- <tfilipe-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 12:17:36 by tfilipe-          #+#    #+#             */
/*   Updated: 2025/07/31 14:49:24 by tfilipe-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

int	ft_atoi(const char *str)
{
	int	i;
	int	signal;
	int	result;

	i = 0;
	signal = 1;
	result = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			signal = -signal;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = (result * 10) + (str[i] - 48);
		i++;
	}
	return (result * signal);
}

int ft_atol(char* s)
{
	long res;
	int signal;
	int i;

	i = 0;
	signal = 1;
	res = 0;
	while (s[i] == 32 || (s[i] >= 9 && s[i] <= 13))
		i++;
	if (s[i] == '-' || s[i] == '+')
	{
		if (s[i] == '-')
			signal = -signal;
		i++;
	}
	while (s[i] && (s[i] >= '0' && s[i] <= '9'))
	{
		res = (res * 10) + (s[i] - 48);
		i++;
	}
	return (res * signal);
}

int	only_num(char **argv)
{
	int	i;
	int j;
	long tmp;

	i = 1;
	while (argv[i])
	{
		j = 0;
		if (argv[i][j] == '+' || argv[i][j] == '-')
			j++;
		while (argv[i][j])
		{
			if (argv[i][j] < '0' || argv[i][j] > '9')
				return (0);
			j++;
		}
		tmp = ft_atol(argv[i]);
		if (tmp < 1 || tmp > INT_MAX)
			return (0);
		i++;
	}
	return (1);
}


