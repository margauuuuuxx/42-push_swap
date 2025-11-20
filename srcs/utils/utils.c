/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marlonco <marlonco@students.s19.be>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 14:15:52 by marlonco          #+#    #+#             */
/*   Updated: 2025/11/18 13:39:15 by marlonco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/push_swap.h"

long long	ft_atoi(const char *str)
{
	int			i;
	int			is_neg;
	long long	res;

	i = 0;
	while (str[i] == '\t' || str[i] == '\n' || str[i] == '\v' || str[i] == '\f'
		|| str[i] == '\r' || str[i] == ' ')
		i++;
	if (str[i] == '-')
		is_neg = -1;
	else
		is_neg = 1;
	if (is_neg == -1 || str[i] == '+')
		i++;
	res = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = (res * 10) + (str[i++] - '0');
	}
	return (res * is_neg);
}

size_t	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	output_message(char *str)
{
	size_t	len;

	len = ft_strlen(str);
	if (!write(2, str, len))
		return ;
}

void	copy_stack(int *cpy, t_stack *a)
{
	int	i;

	i = 0;
	while (i <= a->top)
	{
		cpy[i] = a->values[i];
		i++;
	}
}

int	int_sqrt(int n)
{
	int	x;

	x = 0;
	while ((x + 1) * (x + 1) <= n)
		x++;
	return (x);
}
