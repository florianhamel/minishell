/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhamel <fhamel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 12:25:53 by fhamel            #+#    #+#             */
/*   Updated: 2019/10/17 13:04:52 by fhamel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		get_div(int n)
{
	long	div;

	div = 1;
	while (n / div)
		div *= 10;
	if (n != 0)
		div /= 10;
	return (div);
}

int		get_alloc(int n)
{
	long	div;
	int		to_alloc;

	div = 1;
	to_alloc = 1;
	while (n / div)
	{
		div *= 10;
		to_alloc++;
	}
	return (to_alloc);
}

char	*get_nbr(long div, int n, char *nbr)
{
	long	nb;
	int		i;

	nb = (long)n;
	if (nb < 0)
	{
		nbr[0] = '-';
		nb = -nb;
		i = 1;
	}
	else
		i = 0;
	while (div > 0)
	{
		nbr[i] = nb / div + '0';
		nb -= nb / div * div;
		div /= 10;
		i++;
	}
	nbr[i] = '\0';
	return (nbr);
}

char	*ft_itoa(int n)
{
	long	div;
	int		to_alloc;
	char	*nbr;

	div = get_div(n);
	to_alloc = get_alloc(n);
	if (!(nbr = (char *)malloc(sizeof(char) * (to_alloc + 1))))
		return (0);
	nbr = get_nbr(div, n, nbr);
	return (nbr);
}
