/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclen.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikarjala <ikarjala@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 19:19:19 by ikarjala          #+#    #+#             */
/*   Updated: 2022/03/23 19:44:43 by ikarjala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_lstclen(t_list *lst, t_list *target)
{
	size_t	len;

	len = 0;
	while (lst && lst != target)
	{
		len++;
		lst = lst->next;
	}
	return (len);
}
