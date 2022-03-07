/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikarjala <ikarjala@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 17:45:37 by ikarjala          #+#    #+#             */
/*   Updated: 2022/02/22 11:47:21by ikarjala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

//DEBUG ===
static void	print_mem(char *str, size_t len)
{
	#define PUTCHR(c) write(1, c, 1)
	while (len-- > 0)
	{
		if (*str == 0)
			PUTCHR("0");
		else if (*str == '\n')
			PUTCHR("%%");
		else if (ft_isprint(*str))
			PUTCHR(str);
		else
			PUTCHR("?");
		str++;
	}
}
//DEBUG ===

static size_t	lst_contentlen(t_list *lst)
{
	size_t	len;

	len = 0;
	while (lst)
	{
		if (lst->content)
			len += lst->content_size;
		lst = lst->next;
	}
	return (len);
}

static char		*ft_lst_tostr(t_list *lst)
{
	size_t	len;
	char	*str;

	int index = 1; //DEBUG

	len = lst_contentlen(lst);
	if (len == 0)
		return (NULL);
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	// DEBUG =====
	ft_putstr("total content len:  ");
	ft_putnbr_fd((int)lst_contentlen(lst), 1);
	write(1, "\n", 1);

	ft_putstr("allocated str size:  ");
	ft_putnbr((int)len + 1);
	write(1, "\n", 1);
	// DEBUG =====
	str[len] = 0;
	len = 0;
	while (lst)
	{
		// DEBUG =====
		ft_putnbr(index++);
		ft_putstr(" # attempting to memmove: \'");
		//write(1, lst->content, lst->content_size);
		print_mem(lst->content, lst->content_size);
		ft_putstr("\' into \'");
		//ft_putstr(str);
		print_mem(str, len);
		ft_putstr("\' at index [");
		ft_putnbr((int)len);
		// write(1, str, BUFF_SIZE);
		ft_putendl("]");
		// DEBUG =====

		ft_memmove(&(str[len]), lst->content, lst->content_size);
		//ft_memcpy
		len += lst->content_size;
		lst = lst->next;
	}
	ft_putstr("new string is:  \'"); // DEBUG
	print_mem(str, len);
	// ft_putstr(str); //DEBUG
	ft_putendl("\'");
	ft_putendl("(returning)");
	return (str);
}

static void		lstrm(void *node, size_t size)
{
	if (!node)
		return ;
	ft_bzero(node, size);
	free(node);
}

static t_list	*ft_lstinit(size_t elemc, size_t size)
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
			ft_lstdel(&old, &lstrm);
			return (NULL);
		}
		node->next = old;
		old = node;
	}
	return (node);
}

static size_t	ft_strni(const char *str, int c, size_t size)
{
	size_t	len;

	len = 0;
	while (len < size && *str != c)
	{
		len++;
		str++;
	}
	return (len);
}

int	get_next_line(const int fd, char **line)
{
	static t_buffer	bufs[FD_MAX];
	t_list			*node;
	ssize_t			rbytes;

	if (!line || fd < 0 || !BUFF_SIZE)
		return (RET_ERROR);
	ft_strdel(line);
	if (!bufs[fd].tail)
	{
		bufs[fd].buf = ft_lstinit(1, BUFF_SIZE);
		bufs[fd].tail = bufs[fd].buf;

		node = bufs[fd].tail;
		rbytes = read(fd, node->content, BUFF_SIZE);
		node->content_size = (size_t)rbytes;
	}
	node = bufs[fd].tail;


	size_t loopi = 0; //DEBUG
	loop: // ! NORME !
	bufs[fd].i_nl = ft_strni(&(node->content[bufs[fd].i_nl]), '\n', node->content_size);
	//bufs[fd].i_nl = BUFF_SIZE; //DEBUG
	if (bufs[fd].i_nl == BUFF_SIZE)
	{
		// DEBUG ======
		ft_putstr("loop:  ");
		ft_putnbr_fd((int)loopi++, 1);
		write(1, "\n", 1);
		// DEBUG ======

		node->next = ft_lstinit(1, BUFF_SIZE);
		node = node->next;
		bufs[fd].tail = node;
		rbytes = read(fd, node->content, BUFF_SIZE);
		node->content_size = (size_t)rbytes;

		// DEBUG ======
		ft_putstr("read (");
		ft_putnbr((int)rbytes);
		ft_putstr(") bytes : \'");
		print_mem(node->content, node->content_size);
		ft_putendl("\'");
		// DEBUG ======

		goto loop;
		/* 		if (rbytes < BUFF_SIZE)
					break ; */
	}
	// DEBUG ======
	ft_putstr("newline index:  ");
	ft_putnbr_fd((int)bufs[fd].i_nl, 1);
	write(1, "\n", 1);
	// DEBUG ======

	node = bufs[fd].tail;//DEBUG
	rbytes = (ssize_t)node->content_size; // DEBUG
	node->content_size = bufs[fd].i_nl;//DEBUG
	*line = ft_lst_tostr(bufs[fd].buf);
	node->content_size = (size_t)rbytes; //DEBUG
	ft_lstdel(&bufs[fd].buf, &lstrm);
	if (!*line || !**line)
	{
		ft_putendl("[[ LINE IS EMPTY ! ]]"); //DEBUG
		ft_lstdelone(&bufs[fd].tail, &lstrm); // already freed,  SEGV
		return (RET_EOF);
	}
	bufs[fd].buf = bufs[fd].tail;
	return (RET_READL);
}

// NOTE: ONLY copy up to i_nl bytes from the last buffer!

// we need to preserve remainder after nl when clearing list
//  we need to delete old buffers only up to the last one, exclusive
//  only delete the tail buffer once there's nothing else to read AND we've reached the end of tail buffer

// we try finding nl in the first buffer we init without reading text into it, unsuccessfully,
//  therefore we make a new link an read the first chunk of text into that one, then foolishly think
//  that the first link has valid text and link it together.
