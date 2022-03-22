/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikarjala <ikarjala@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 17:46:50 by ikarjala          #+#    #+#             */
/*   Updated: 2022/03/22 19:41:16 by ikarjala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include "libft.h"
# include <stdio.h>// DEBUG

# define RET_READL	1
# define RET_EOF	0
# define RET_ERROR	-1

# define BUFF_SIZE	4
# define FD_MAX		8192

typedef struct	s_buffer
{
	t_list	*buf;
	t_list	*tail;
	char	*nlp;
}				t_buffer;

int	get_next_line(const int fd, char **line);


 // DEBUG ===
 #ifndef DEBUG_G
	#define PUTCHR(c) write(1, c, 1) // DEBUG
	#define DEBUG_G 1
	#if DEBUG_G
//DEBUG ===========================
	static inline char	*fmem(char *str, size_t size)
	{
		#define FMEM_MAPC	5
		char	*new;
		char	*s;
		char	*m_p;
		const	char	mapfr[FMEM_MAPC] = "\n\t\v\r\0";
		const	char	mapto[FMEM_MAPC] = "%\t^~0";
		const	char	noprint = '?';

		if (!str || !size)
			return (NULL);
		new = (char *)malloc(sizeof(char) * size + 1);
		if (!new)
			return (NULL);
		new[size] = 0;
		s = new;
		while (size-- > 0)
		{
			m_p = ft_memchr(mapfr, *str, FMEM_MAPC);
			if (m_p)
				*s = mapto[m_p - mapfr];
			else if (ft_isprint(*str))
				*s = *str;
			else
				*s = noprint;
			s++;
			str++;
		}
		s = NULL;
		return (new);
	}

	static inline void	print_mem(char *str, size_t len)
	{
		char *new;

		if (!str || !len)
			return ;
		new = fmem(str, len);
		if (!new)
			return ;
		ft_putstr(new);
		ft_bzero(new, len);
		free(new);
		return ;
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
