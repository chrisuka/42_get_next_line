/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikarjala <ikarjala@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 18:45:23 by ikarjala          #+#    #+#             */
/*   Updated: 2022/04/01 16:21:47 by ikarjala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static t_list	*addbuffer(int fd, size_t size, ssize_t *rbytes, t_buffer *buf)
{
	t_list	*new;
	size_t	u_rb;

	new = ft_lstinit(1, size);
	if (!new)
		return (NULL);
	*rbytes = read(fd, new->content, size);
	u_rb = (size_t) * rbytes;
	buf[fd].f_eof = u_rb < BUFF_SIZE;
	new->content_size = u_rb;
	ft_bzero(&new->content[u_rb], size - u_rb);
	return (new);
}

static t_list	*dupremainder(t_list *node, void *nlp)
{
	size_t	nli;
	t_list	*tmp;

	nli = 0;
	if (node->content_size > 0)
		nli = (size_t)(nlp - node->content);
	tmp = NULL;
	if (nli + 1 < node->content_size)
	{
		tmp = ft_lstnew(&nlp[1], node->content_size - nli - 1);
		ft_bzero(nlp, node->content_size - nli);
	}
	node->content_size = nli;
	return (tmp);
}

static inline t_bool	find_nl(t_list *node, void **nlpout)
{
	*nlpout = ft_memchr(node->content, '\n', node->content_size);
	return (*nlpout != NULL);
}

static inline t_bool	nukecheck(t_bool condition, t_buffer *buf, int fd)
{
	if (condition)
	{
		ft_lstdel(&buf[fd].buf, &ft_memclr);
		buf[fd].f_eof = FT_FALSE;
	}
	return (condition);
}

int	get_next_line(const int fd, char **line)
{
	static t_buffer	bufs[FD_MAX];
	t_list			*node;
	void			*nlp;
	ssize_t			rbytes;

	if (!line || fd < 0 || !BUFF_SIZE || fd > FD_MAX)
		return (RET_ERROR);
	if (!bufs[fd].buf)
		bufs[fd].buf = addbuffer(fd, BUFF_SIZE, &rbytes, bufs);
	node = bufs[fd].buf;
	while (!find_nl(node, &nlp) && node->content_size > 0)
	{
		node->next = addbuffer(fd, BUFF_SIZE, &rbytes, bufs);
		if (nukecheck((!node->next || rbytes < 0), bufs, fd))
			return (RET_ERROR);
		node = node->next;
	}
	node = dupremainder(node, nlp);
	*line = ft_lststr(bufs[fd].buf);
	ft_lstdel(&bufs[fd].buf, &ft_memclr);
	if (nukecheck((!*line && !node && bufs[fd].f_eof), bufs, fd))
		return (RET_EOF);
	bufs[fd].buf = node;
	return (RET_READL);
}
