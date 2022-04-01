/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstinit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikarjala <ikarjala@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 19:00:14 by ikarjala          #+#    #+#             */
/*   Updated: 2022/03/23 19:10:28 by ikarjala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstinit(size_t elemc, size_t size)
{
	t_list	*node;
	t_list	*old;

	node = NULL;
	old = NULL;
	while (elemc-- > 0)
	{
		node = (t_list *)malloc(sizeof(t_list));
		node->content_size = size;
		node->content = malloc(sizeof(char) * size);
		if (!node || !node->content)
		{
			ft_lstdel(&old, &ft_memclr);
			return (NULL);
		}
		node->next = old;
		old = node;
	}
	return (node);
}
