/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikarjala <ikarjala@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 18:45:23 by ikarjala          #+#    #+#             */
/*   Updated: 2022/04/10 19:57:21 by ikarjala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

#include "eval_tests/ft_debugtools.h"

static t_list *addbuffer(int fd, t_buffer *buf)
{
	t_list	*new;
	ssize_t	rbytes;
	size_t	u_rb;

	new = ft_lstinit(1, BUFF_SIZE);
	if (!new)
		return (NULL);
	rbytes = read(fd, new->content, BUFF_SIZE);
	if (rbytes < 0)
	{
		ft_lstdel(&new, &ft_memclr);
		return (NULL);
	}
	u_rb = (size_t)rbytes;
	buf[fd].f_eof = u_rb < BUFF_SIZE;
	new->content_size = u_rb;
	ft_bzero(&new->content[u_rb], BUFF_SIZE - u_rb);
	return (new);
}

static inline t_bool	nukecheck(t_bool condition, t_buffer *buf, int fd)
{
	if (condition)
	{
		ft_lstdel(&buf[fd].buf, &ft_memclr);
		buf[fd].nlp = NULL;
		buf[fd].f_eof = FT_FALSE;
	}
	return (condition);
}

static t_list	*getlinep(t_list *node, void *beg, void *end)
{
	t_list	*new;

	if (!beg)
		beg = node->content;
	if (!end)
		end = &node->content[node->content_size - 1];
	if (beg >= end)
		return (NULL);
	new = (t_list *)malloc(sizeof(t_list));
	if (!new)
		return (NULL);
	new->content = beg;
	new->content_size = (size_t)(end - beg);
	new->next = NULL;
	return (new);
}

static inline t_bool	find_nl(t_list *node, void **nlp_o)
{
	if (!*nlp_o)
		*nlp_o = node->content;
	*nlp_o = ft_memchr(*nlp_o, '\n', node->content_size);
	return (*nlp_o != NULL);
}

int	get_next_line(const int fd, char **line)
{
	static t_buffer	bufs[FD_MAX];
	t_list			*node;
	t_list			*tmp;
	void			*nlp;

	if (nukecheck(!line || fd < 0 || !BUFF_SIZE || fd > FD_MAX, bufs, fd))
		return (RET_ERROR);
	nlp = bufs[fd].nlp;
	if (!bufs[fd].buf)
		bufs[fd].buf = addbuffer(fd, bufs);
	if (nukecheck(!bufs[fd].buf, bufs, fd))
		return (RET_ERROR);
	node = bufs[fd].buf;

	if (nlp && nlp > node->content && nlp + 1 < &node->content[node->content_size])
		bufs[fd].buf = getlinep(node, nlp, bufs[fd].nlp);

	while (!find_nl(node, &bufs[fd].nlp) && !bufs[fd].f_eof)
	{
		node->next = addbuffer(fd, bufs);
		if (nukecheck(!node->next, bufs, fd))
			return (RET_ERROR);
		tmp = node;
		node = node->next;
	}

	tmp->next = getlinep(node, nlp, bufs[fd].nlp);
	*line = ft_lststr(bufs[fd].buf);

	printlst(bufs[fd].buf);
	tmp->next->content = NULL;
	ft_lstdel(&bufs[fd].buf, &ft_memclr);

	if (nukecheck((!**line && !node && bufs[fd].f_eof && !bufs[fd].nlp), bufs, fd)) //NORME
		return (RET_EOF);
	bufs[fd].buf = node;
	bufs[fd].nlp++;
	return (RET_READL);
}
