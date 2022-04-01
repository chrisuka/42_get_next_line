/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikarjala <ikarjala@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 19:21:41 by ikarjala          #+#    #+#             */
/*   Updated: 2021/12/18 00:15:17 by ikarjala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memalloc(size_t size)
{
	char	*ptr;

	if (size == 0)
		return (NULL);
	ptr = (char *)malloc(size);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, size);
	return ((void *)ptr);
}
