/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aisdaoun <aisdaoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 17:50:32 by aisdaoun          #+#    #+#             */
/*   Updated: 2025/01/23 18:01:03 by aisdaoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static int	_is_digit(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

static int	_stoi_h(char *str, int *i, int *s)
{
	int		nine;
	int		res;

	res = 0;
	while (str[*i] == ' ')
		(*i)++;
	if (str[*i] == '+' || str[*i] == '-')
	{
		if (str[*i] == '-')
			*s = -1;
		++*i;
	}
	while (str[*i] && str[*i] == '0')
		(*i)++;
	nine = -1;
	while (str[*i] && _is_digit(str[*i]) && ++nine < 9)
		res = res * 10 + (str[(*i)++] - '0');
	return (res);
}

static long	_stoi(char *str)
{
	int	i;
	int	res;
	int	s;

	i = 0;
	s = 1;
	if (str == NULL)
		return (10000000000);
	res = _stoi_h(str, &i, &s);
	if (str[i] && _is_digit(str[i]))
	{
		if (res > 214748364)
			return (10000000000);
		else
		{
			if (str[i + 1] && _is_digit(str[i + 1]))
				return (10000000000);
			if (s == 1 && res == 214748364 && str[i] > '7')
				return (10000000000);
			if (s == -1 && res == 214748364 && str[i] > '8')
				return (10000000000);
			res = res * 10 + (str[i] - '0');
		}
	}
	return (res * s);
}

long	c_stoi_(char *arg)
{
	long	stoi_res;

	stoi_res = _stoi(arg);
	if (stoi_res == STOI_F || stoi_res < 0)
	{
		printf(RED"invalid args\n"RESET);
		return (-1);
	}
	return (stoi_res);
}
