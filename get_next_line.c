/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikarjala <ikarjala@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 19:50:25 by ikarjala          #+#    #+#             */
/*   Updated: 2022/03/31 15:58:20by ikarjala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static t_list	*addbuffer(int fd, size_t size, size_t *rbytes)
{
	t_list	*new;

	new = ft_lstinit(1, size);
	if (!new)
		return (NULL);
	*rbytes = (size_t)read(fd, new->content, size);
	new->content_size = *rbytes;
	ft_bzero(&new->content[*rbytes], size - *rbytes);
	return (new);
}

int	get_next_line(const int fd, char **line)
{
	static t_buffer	bufs[FD_MAX];
	t_list			*node;
	t_list			*tmp;
	size_t			rbytes;
	size_t			nli;

	if (!line || fd < 0 || !BUFF_SIZE || fd > FD_MAX)
		return (RET_ERROR);
	if (!bufs[fd].tail)
		bufs[fd].tail = addbuffer(fd, BUFF_SIZE, &rbytes);
	bufs[fd].buf = bufs[fd].tail;
	node = bufs[fd].tail;
	bufs[fd].nlp = ft_memchr(node->content, '\n', node->content_size);
	while (!bufs[fd].nlp && node->content_size > 0)
	{
		node->next = addbuffer(fd, BUFF_SIZE, &rbytes);
		node = node->next;
		bufs[fd].nlp = ft_memchr(node->content, '\n', node->content_size);
	}
	nli = 0;
	if (node->content_size > 0)
		nli = (size_t)bufs[fd].nlp - (size_t)node->content;
	tmp = NULL;
	if (nli + 1 < node->content_size)
	{
		tmp = ft_lstnew(&bufs[fd].nlp[1], node->content_size - nli - 1);
		ft_bzero(bufs[fd].nlp, node->content_size - nli);
	}
	node->content_size = nli;
	*line = ft_lststr(bufs[fd].buf);
	bufs[fd].nlp = NULL;
	ft_lstdel(&bufs[fd].buf, &ft_memclr);
	if (!*line && !tmp && !rbytes)
	{
		tmp = addbuffer(fd, BUFF_SIZE, &rbytes);
		if (!rbytes)
		{
			ft_lstdelone(&tmp, &ft_memclr);
			bufs[fd].tail = NULL;
			return (RET_EOF);
		}
	}
	bufs[fd].tail = tmp;
	return (RET_READL);
}

// FIX norme in this file (get_next_line is over 25 lines long)
// REMOVE DEBUG

// YOU FOOL REMOVE THE LICENSE and any other extra files FROM LIBFT OR YOU'RE TOAST!

// TODO: submit !!
