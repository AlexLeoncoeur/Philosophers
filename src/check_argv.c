/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_argv.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarenas- <aarenas-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 12:38:49 by aarenas-          #+#    #+#             */
/*   Updated: 2024/09/03 14:49:17 by aarenas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static int	ignorespace(char c)
{
	if (c == '\t' || c == '\n' || c == '\v' || c == '\f'
		|| c == '\r' || c == ' ')
		return (1);
	else
		return (0);
}

int	ft_nb_checker(const char *str)
{
	int		i;
	int		sign;
	long	result;

	sign = 1;
	result = 0;
	i = 0;
	while (ignorespace(str[i]))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = (result * 10) + str[i] - 48;
		i++;
	}
	result *= sign;
	if (result < 0 || result > MAX)
		return (1);
	return (0);
}

int	ft_atoi(const char *str)
{
	int		i;
	int		sign;
	long	result;

	sign = 1;
	result = 0;
	i = 0;
	while (ignorespace(str[i]))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = (result * 10) + str[i] - 48;
		i++;
	}
	result *= sign;
	return (result);
}

int	ft_check_char(char **numbers)
{
	int	i;
	int	j;

	i = 0;
	if (!numbers[i])
		ft_puterrorstr("Error: Argument is not a number\n", NULL);
	while (numbers[i])
	{
		j = 0;
		if (numbers[i][j] == '-' || numbers[i][j] == '+')
			j++;
		while (numbers[i][j])
		{
			if ((numbers[i][j] < '0' || numbers[i][j] > '9'))
				ft_puterrorstr("Error: Argument is not a number\n", NULL);
			j++;
		}
		i++;
	}
	return (0);
}
