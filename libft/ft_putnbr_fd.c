/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikarjala <ikarjala@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 19:05:20 by ikarjala          #+#    #+#             */
/*   Updated: 2022/03/29 18:08:39 by ikarjala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	int		pow;
	int		div;
	t_bool	ltz;

	ltz = n < 0;
	write(fd, "-", ltz);
	pow = ft_log10(n);
	div = ft_pow(10, pow) * (1 | -ltz);
	while (pow-- >= 0)
	{
		ft_putchar_fd((char)(n / div % 10 + '0'), fd);
		div /= 10;
	}
}
