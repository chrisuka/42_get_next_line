/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikarjala <ikarjala@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 17:46:50 by ikarjala          #+#    #+#             */
/*   Updated: 2022/03/19 17:25:49 by ikarjala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include "libft.h"
#include <stdio.h>// DEBUG

# define RET_READL	1
# define RET_EOF	0
# define RET_ERROR	-1

# define BUFF_SIZE	4
# define FD_MAX		8192

typedef struct	s_buffer
{
	t_list	*buf;
	t_list	*tail;
	size_t	i_nl;
}				t_buffer;

int	get_next_line(const int fd, char **line);


//DEBUG ===========================
 #ifndef DEBUG_G
	#define PUTCHR(c) write(1, c, 1) // DEBUG
	#define DEBUG_G 1
	#if DEBUG_G
	static inline void	print_mem(char *str, size_t len)
	{
		while (len-- > 0)
		{
			if (*str == 0)
				PUTCHR("0");
			else if (*str == '\n')
				PUTCHR("%%");
			else if (*str == '\v' || *str == '\r')
				PUTCHR("~");
			else if (ft_isprint(*str))
				PUTCHR(str);
			else
				PUTCHR("?");
			str++;
		}
	}

	static inline char	*fmem(char *str, size_t size)
	{
		char	*new;
		char	*s;

		if (!str)
			return (NULL);
		new = (char *)malloc(sizeof(char) * size + 1);
		if (!new)
			return (NULL);
		ft_memset(new, '0', size); //DEBUG
		new[size] = 0;
		s = new;
		while (size-- > 0 && *str)
		{
			if (*str == '\n')
				*s = '%';
			else if (*str == '\v' || *str == '\r')
				*s = '~';
			else if (ft_isprint(*str))
				*s = *str;
			else
				*s = '?';
			s++;
			str++;
		}
		s = NULL;
		return (new);
	}

	static inline void		printbuf(t_list *lst)
	{
		t_list	*buf;
		size_t	i;
		char	*cont;

		i = 0;
		buf = lst;
		while (buf)
		{
			cont = fmem((char *)buf->content, buf->content_size);
			printf("[N%lu](%lu): '%s' -> ", i, buf->content_size, cont);
			ft_strdel(&cont);
			i++;
			buf = buf->next;
		}
		printf("[NULL]\n");
		buf = lst;
		while (i-- > 0)
		{
			printf("%p  -> ", buf);
			buf = buf->next;
		}
		printf("0x0\n");
	}

	static inline void unuse()
	{
		char *str = fmem("help", 4);
		print_mem(str, 4);
		printbuf(NULL);
		ft_strdel(&str);
		if (rand() > 0)
			unuse();
	}
#endif
 #endif
//DEBUG ===========================

#endif
