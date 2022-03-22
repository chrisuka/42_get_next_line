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

#define DEBUG	0 //DEBUG
#define VERBOSE	1 //DEBUG


#pragma region SUBFUNCTIONS



#if DEBUG_G
char *fmem(char *str, size_t size);
void print_mem(char *str, size_t len);
void printbuf(t_list *buf);
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

#if 0
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
	//index = -1UL;
	//while (++index < count && tail)
	while (count-- > 0 && tail)
	{
#if DEBUG
		//DEBUG ======
		cont = fmem(tail->content, tail->content_size);
		printf("\tdeleting [N%lu] : \'%s\' %p\n", index++, cont, tail);
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
	printf("we cut (%lu) elements\n", index - start); //DEBUG
#endif
	head->next = tail;
	if (start == 0)
		*alst = tail;
#if DEBUG
	printbuf(*alst);//DEBUG
#endif
	return (0);
}
#endif

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
	free(node);
}

#if 1
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
#endif

#if DEBUG && 0
// DEBUG ====
static void test_lst()
{
	t_list	*lst;
	t_list	*node;
	int		c;

	lst = NULL;
#if DEBUG && DEBUG_G
	printf("initial list status:\n");
	printbuf(lst);
	printf("intializing a new list of 5 nodes of size %i\n", BUFF_SIZE);
#endif

	lst = ft_lstinit(5, BUFF_SIZE);

	node = lst;
	c = 0;
	while (node)
	{
		ft_memset(node->content, c++ % 26 + 'a' , BUFF_SIZE);
		node = node->next;
	}
#if DEBUG && DEBUG_G
	printbuf(lst);
	printf("cutting elements 1, 2 and 3\n");
#endif

	ft_lstcut(&lst, 1, 3, &lstrm);

#if DEBUG && DEBUG_G
	printf("post deletion:\n");
	printbuf(lst);
#endif
#if DEBUG && DEBUG_G
	printf("clearing list\n");
#endif

	ft_lstdel(&lst, &lstrm);

#if DEBUG && DEBUG_G
	printbuf(lst);
	printf("lst testing complete.\n");
#endif
}
// DEBUG ====
#endif

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

#pragma endregion



// GNL BEGIN ====================================================================
int	get_next_line(const int fd, char **line)
{
	static t_buffer	bufs[FD_MAX];
	t_list	*node;
	t_list	*tmp;
	size_t	rbytes;
	size_t	nli;

	if (!line || fd < 0 || !BUFF_SIZE || fd > FD_MAX)
		return (RET_ERROR);
	ft_strdel(line);
	if (!bufs[fd].tail)
		bufs[fd].tail = addbuffer(fd, BUFF_SIZE, &rbytes);
	bufs[fd].buf = bufs[fd].tail;
	node = bufs[fd].tail;

loop: // ! NORME !

	bufs[fd].nlp = ft_memchr(node->content, '\n', node->content_size);
	if (!bufs[fd].nlp && node->content_size > 0)
	{
		node->next = addbuffer(fd, BUFF_SIZE, &rbytes);
		node = node->next;
		goto loop;
	}
	nli = 0;
	if (node->content_size > 0)
		nli = (size_t)bufs[fd].nlp - (size_t)node->content;

	// AFTER NEWLINE DUPLICATION HANDLING ------------------
	tmp = NULL;
	if (nli + 1 < node->content_size)
	{
		tmp = ft_lstnew(&bufs[fd].nlp[1], node->content_size - nli - 1);
		ft_bzero(bufs[fd].nlp, node->content_size - nli);
	}
	// AFTER NEWLINE DUPLICATION HANDLING ------------------
	node->content_size = nli;



#if DEBUG
	// DEBUG
	printbuf(bufs[fd].buf);
	ft_putstr("tmp : ");
	if (!tmp)
		ft_putendl("(null)");
	else
	{
		PUTCHR("\'");
		print_mem(tmp->content, tmp->content_size);
		PUTCHR("\'");
	}
	PUTCHR("\n");
	// DEBUG
#endif

	// CREATE SINGULAR STRING FROM ALL NODE CONTENTS
	*line = ft_lststr(bufs[fd].buf);

	bufs[fd].nlp = NULL;

	ft_lstdel(&bufs[fd].buf, &lstrm); // FIXME: SEGV on 10.txt

	if (!*line && !tmp && !rbytes)
	{
		tmp = addbuffer(fd, BUFF_SIZE, &rbytes);
		if (!rbytes)
		{
			ft_lstdelone(&tmp, &lstrm);
			return (RET_EOF);
		}
	}
	bufs[fd].tail = tmp;
	return (RET_READL);
}

// TODO: fix premature EOF on nlnl.txt
// NOTE: don't forget to save new functions
// NOTE: don't forget to commit libft changes
// TODO: fix norme
// TODO: submit !!
