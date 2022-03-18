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
#include <stdio.h>// DEBUG


#define DEBUG	0 //DEBUG
#define VERBOSE	0 //DEBUG

#define PUTCHR(c) write(1, c, 1) // DEBUG
#if DEBUG
//DEBUG ===
static void	print_mem(char *str, size_t len)
{
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
static char	*fmem(char *str, size_t len)
{
	char	*new;
	char	*s;

	if (!str)
		return ("(null)");
	new = (char *)malloc(sizeof(char) * ft_strlen(str));
	if (!new)
		return ("(malloc fail)");
	s = new;
	new[len] = 0;
	while (len-- > 0)
	{
		if (*str == '\n')
			*s = '%';
		else if (!ft_isprint(*str))
			*s = '?';
		else
			*s = *str;
		s++;
		str++;
	}
	return (new);
}
//DEBUG ===
#endif

#if DEBUG
// DEBUG =====
static void		printbuf(t_list *buf)
{
	size_t	i;
	char	*cont;

	i = 0;
	while (buf)
	{
		cont = fmem((char *)buf->content, buf->content_size);
		printf("[N%lu](%lu): '%s' -> ", i, buf->content_size, cont);
		ft_strdel(&cont);
		i++;
		buf = buf->next;
	}
	printf("[NULL]\n");
}

//DEBUG ===
#endif


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

static size_t	ft_lstclen(t_list *lst, t_list *target)
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

static int		ft_lstcut(t_list **alst, size_t start, size_t count,
	void (*del)(void *, size_t))
{
	t_list	*head;
	t_list	*tail;
	t_list	*temp;
	size_t	index;

#if DEBUG
	char *cont;
#endif

	if (count == 0 || !alst)
		return (-1);
	head = *alst;
	index = 0;
#if DEBUG
	printf("index = %lu\n", index); //DEBUG
#endif
	while (++index < start)
	{
		if (!head)
			return (-1);
		head = head->next;
	}
	tail = head->next;
	if (start == 0)
		tail = head;
#if DEBUG
	printf("cutting list...\n"); // DEBUG
	printbuf(*alst);//DEBUG
#endif
	index = -1UL;
	while (++index < count && tail)
	{
#if DEBUG
		//DEBUG ======
		cont = fmem(tail->content, tail->content_size);
		printf("\tdeleting [N%lu] : \'%s\'\n", index, cont);
		ft_strdel(&cont);
		// DEBUG ======
#endif
		temp = tail->next;
		//ft_lstdelone(&tail, del);
		del(tail->content, tail->content_size);
		free(tail);
		tail = temp;
	}
#if DEBUG
	printf("we cut (%lu) elements\n", index); //DEBUG
#endif
	head->next = tail;
	if (start == 0)
	{
		head = NULL;
		*alst = tail;
	}
#if DEBUG
	printbuf(*alst);//DEBUG
#endif
	return (0);
}

static char		*ft_lststr(t_list *lst)
{
	size_t	len;
	char	*str;

#if DEBUG
	int index = 1; //DEBUG
#endif

	len = lst_contentlen(lst);
	if (len == 0)
		return (NULL);
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
#if DEBUG
	// DEBUG =====
	ft_putstr("total content len:  ");
	ft_putnbr_fd((int)lst_contentlen(lst), 1);
	write(1, "\n", 1);

	ft_putstr("allocated str size:  ");
	ft_putnbr((int)len + 1);
	PUTCHR("\n");
	// DEBUG =====
#endif
	str[len] = 0;
	len = 0;
	while (lst)
	{
#if DEBUG
		// DEBUG =====
		ft_putnbr(index++);
		ft_putstr(" # attempting to memmove: \'");
		print_mem(lst->content, lst->content_size);
		ft_putstr("\' into \'");
		print_mem(str, len);
		ft_putstr("\' at index [");
		ft_putnbr((int)len);
		ft_putendl("]");
		// DEBUG =====
#endif

		ft_memmove(&(str[len]), lst->content, lst->content_size);
		len += lst->content_size;
		lst = lst->next;
	}
#if DEBUG
	// DEBUG =====
	ft_putstr("new string is:  \'");
	print_mem(str, len);
	ft_putendl("\'");
	ft_putendl("(returning)");
	// DEBUG =====
#endif
	return (str);
}

static void		lstrm(void *node, size_t size)
{
	if (!node)
		return ;
	ft_bzero(node, size);
	ft_memdel(&node);
	//free(node);
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

static size_t	ft_strni(const char *str, int c, size_t n)
{
	size_t	len;

#if DEBUG && VERBOSE >= 3
	// DEBUG ====
	ft_putendl("debug");
/* 	if (!str || !*str)
	{

	} */
	ft_putendl("str is not null");
	printf("address of str: %p\naddress of &str: %p\n", str, &str);
	// print_mem((char *)str, BUFF_SIZE);
	PUTCHR("\n");
	// DEBUG ====
#endif
	len = 0;
	while (len < n && *str != c)
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
	size_t			tmp;

#if DEBUG
	PUTCHR("\n");
#endif
	if (!line || fd < 0 || !BUFF_SIZE || fd > FD_MAX)
		return (RET_ERROR);
	ft_strdel(line);
	if (!bufs[fd].buf)
	{
#if DEBUG
		ft_putendl("INITIAL LINK -------------------------"); //DEBUG
#endif
		bufs[fd].buf = ft_lstinit(1, BUFF_SIZE);
		bufs[fd].tail = bufs[fd].buf;

		node = bufs[fd].tail;
		rbytes = read(fd, node->content, BUFF_SIZE);
		node->content_size = (size_t)rbytes;
#if DEBUG
		// DEBUG ======
		ft_putstr("read (");
		ft_putnbr((int)rbytes);
		ft_putstr(") bytes : \'");
		print_mem(node->content, (size_t)rbytes);
		ft_putendl("\' into HEAD");
		// DEBUG ======
#endif
	}
	node = bufs[fd].tail;
#if DEBUG
	// DEBUG ====
	ft_putendl("about to perform node checks");
	if (!bufs[fd].tail)
		ft_putendl("node is null");
	else if (!bufs[fd].tail->content_size)
		ft_putendl("node content_size is zero");
	else if (!bufs[fd].tail->content)
		ft_putendl("node content is null");
	#if VERBOSE >= 2
	printf("buf is at  %p\ntail is at %p\n", bufs[fd].buf, bufs[fd].tail);
	printf("current node count is  %lu\n", ft_lstclen(bufs[fd].buf, NULL)); // SEGV
	// printbuf(bufs[fd].buf);
	print_mem(node->content, node->content_size);
	PUTCHR("\n");
	// DEBUG ====
	#endif
#endif

#if DEBUG
	size_t	loopi = 0; //DEBUG
#endif
	loop: // ! NORME !

#if DEBUG && VERBOSE >= 3
	ft_putendl("about to strni"); // DEBUG
#endif
	bufs[fd].i_nl = ft_strni(node->content, '\n', node->content_size);
#if DEBUG && VERBOSE >= 3
	ft_putendl("strni success"); // DEBUG
	//bufs[fd].i_nl = BUFF_SIZE; //DEBUG
#endif
	if (bufs[fd].i_nl == BUFF_SIZE)
	{
#if DEBUG
		// DEBUG ======
		ft_putstr("loop:  ");
		ft_putnbr_fd((int)loopi++, 1);
		write(1, "\n", 1);
		printbuf(bufs[fd].buf);
		// DEBUG ======
#endif

		node->next = ft_lstinit(1, BUFF_SIZE);
		node = node->next;
		bufs[fd].tail = node;
		rbytes = read(fd, node->content, BUFF_SIZE);
		node->content_size = (size_t)rbytes;

#if DEBUG
		// DEBUG ======
		ft_putstr("read (");
		ft_putnbr((int)rbytes);
		ft_putstr(") bytes : \'");
		print_mem(node->content, node->content_size);
		ft_putendl("\'");
		// DEBUG ======
#endif

		goto loop;
		/* 		if (rbytes < BUFF_SIZE)
					break ; */
	}
#if DEBUG
	// DEBUG ======
	ft_putstr("newline index:  ");
	ft_putnbr_fd((int)bufs[fd].i_nl, 1);
	ft_putstr("  \'");
	print_mem(bufs[fd].tail->content, bufs[fd].tail->content_size);
	ft_putendl("\'");
	// DEBUG ======
#endif

	// hack node's content_size temporarily for lststr
	node = bufs[fd].tail; // DEBUG
	tmp = node->content_size; // DEBUG
	node->content_size = bufs[fd].i_nl; // DEBUG

	*line = ft_lststr(bufs[fd].buf);
	// now return it to its real value

	node->content_size = tmp; //DEBUG

	// del all but last node
	ft_lstcut(&bufs[fd].buf, 0, ft_lstclen(bufs[fd].buf, NULL) - 1, &lstrm);
	if ((!*line || !**line) && rbytes < BUFF_SIZE)
	{
#if DEBUG
		ft_putendl("[[ LINE IS EMPTY ! ]]"); //DEBUG
#endif
		ft_lstcut(&bufs[fd].buf, 0, -1UL, &lstrm);
		//ft_lstdel(&bufs[fd].buf, &lstrm);
		return (RET_EOF);
	}
#if DEBUG
	// DEBUG ======
	ft_putstr("nl index  [");
	ft_putnbr((int)bufs[fd].i_nl);
	ft_putstr("]  vs size  [");
	ft_putnbr((int)node->content_size);
	PUTCHR("]");
	PUTCHR("\n");
	// DEBUG ======
#endif

	// NOTE:  atm, node == bufs[fd].tail
	//node = NULL; //DEBUG
	if (bufs[fd].i_nl < node->content_size - 1)
	{
#if DEBUG && VERBOSE >= 2
		printf("node pos is  %p\n", node);
#endif
		node = ft_lstnew(&node->content[bufs[fd].i_nl + 1], BUFF_SIZE);

#if DEBUG
		// DEBUG ======
		printbuf(bufs[fd].buf);
		ft_putstr("dup the rest of tail into a copy element of size  ");
		ft_putnbr((int)node->content_size);
		ft_putstr(" containing : \'");
		print_mem(node->content, node->content_size);
		PUTCHR("\'");
		PUTCHR("\n");
		// DEBUG ======
#endif
		tmp = BUFF_SIZE - bufs[fd].i_nl - 1;
		// FIXME: this index is wrong, we read on top of existing text!
		rbytes = read(fd, &node->content[tmp], BUFF_SIZE - tmp);
		// update content size of dup tail after reading into it
		node->content_size = tmp + (size_t)rbytes;

#if DEBUG
		// DEBUG ======
		ft_putstr("read (");
		ft_putnbr((int)rbytes);
		ft_putstr(") bytes : \'");
		print_mem(&node->content[tmp], (size_t)rbytes);
		ft_putendl("\' into tail");
		// DEBUG ======
#endif
	}
	else
		node = NULL;
	ft_lstdelone(&bufs[fd].tail, &lstrm);
#if 0
	printf("address of node is  %p\nwith a size of (%lu)\n", node, node->content_size);
	printf("before assignment address of tail is  %p\n", bufs[fd].tail);
	printf("before assignment address of buf is  %p\n", bufs[fd].buf);
#endif
#if DEBUG && VERBOSE >= 3
	ft_putendl("pre  assign"); //DEBUG
#endif
	bufs[fd].tail = node ? node : NULL;// NORME
	bufs[fd].buf = bufs[fd].tail ? bufs[fd].tail : NULL; //NORME
#if DEBUG && VERBOSE >= 3
	ft_putendl("post assign"); //DEBUG
	printbuf(bufs[fd].buf); // DEBUG
#endif
	return (RET_READL);
}

// FIXME: multiple newlines in a row cause premature EOF!!
// |- this is caused by a nl in index 0, it makes lststr think the content is empty and returns null line
// |_,- how to fix: replace strni with strnchr and get its index another way, use nl == NULL for logic




// BUG  : wtf is happening with the bible?! 00000000000000000 near-endless loop until segfault
// |_,- it seems this was caused by a faulty debugging function

// NOTE: something might be hecked up with the index calculations when filling out the rest of duped tail string
//  |- [yes]
//  |_,-(it seems to sometimes read too many bytes into tail buffer after duplication)

// NOTE: lstcut "just works" because if we are checking 0 (-1) elements it overflows to SIZE_T_MAX
//		but we only iterate while not NULL, therefore we do not need the extra free before EOF

// ----------------------------------------------------------------------------------------------------
//    [CHECK]

// TODO: MAKE SURE lstcut works as expected and its parameters are correct!!

// NOTE: after we dup the rest of the string past nl the content_size changes, this messes with strni(nl)

// TODO: ONLY copy up to i_nl bytes from the last buffer!

// we need to preserve remainder after nl when clearing list
//  we need to delete old buffers only up to the last one, exclusive
//  only delete the tail buffer once there's nothing else to read AND we've reached the end of tail buffer

// we try finding nl in the first buffer we init without reading text into it, unsuccessfully,
//  therefore we make a new link an read the first chunk of text into that one, then foolishly think
//  that the first link has valid text and link it together.
