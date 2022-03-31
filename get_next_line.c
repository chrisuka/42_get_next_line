/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikarjala <ikarjala@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 18:45:23 by ikarjala          #+#    #+#             */
/*   Updated: 2022/03/31 23:11:52 by ikarjala         ###   ########.fr       */
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
		node = node->next;
	}
	node = dupremainder(node, nlp);
	*line = ft_lststr(bufs[fd].buf);
	ft_lstdel(&bufs[fd].buf, &ft_memclr);
	if (!*line && !node && bufs[fd].f_eof)
	{
		bufs[fd].f_eof = FT_FALSE;
		return (RET_EOF);
	}
	bufs[fd].buf = node;
	return (RET_READL);
}

// FIX norme in this file (get_next_line is over 25 lines long) ["FIXED" LMAO]
// REMOVE DEBUG [CHECK]

// NOTE: might want to RET_ERROR if read fails		< ----
// NOTE: libft might actually not be approved by moulinette as a submodule..		< ----

// YOU FOOL REMOVE THE LICENSE and any other extra files FROM LIBFT OR YOU'RE TOAST!

// TODO: submit !!

// =========

// NOTABLE ERRORS AFTER CHANGES:
//	rbytes EOF check will be incorrect if we never call addbuffer
//	if we dont call memchr twice nlp will be NULL and we call addbuffer when we should not
//	buf will stay NULL if its NULL in the beginning

// OTHER NOTES:
//	we might not actually need nlp/tail to be static
//	in which case we can get rid of buf struct and use t_list *[] instead
