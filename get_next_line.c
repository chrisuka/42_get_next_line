/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikarjala <ikarjala@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 17:45:37 by ikarjala          #+#    #+#             */
/*   Updated: 2022/02/04 02:28:24 by ikarjala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	get_next_line(const int fd, char **line)
{
	static char	buf[BUFF_SIZE + 1];
	char		*p_nl;
	size_t		bytes;

	if (!fd)
		return (RET_ERROR);
	buf[BUFF_SIZE] = '\0';
	bytes = read(fd, buf, BUFF_SIZE);
	
	p_nl = ft_strnstr(buf, "\n", BUFF_SIZE);
	ft_memmove(*line, buf, p_nl - buf);

}
/*	LOGIC:
**	read into buffer
**
**	should we allocate buffer in heap??
**	allocate more space for buffer as we read more bytes than it can store..?
**		maybe a linked list of buffers of size BUFF_SIZE ?!
**
**	then find index of first newline
**	memmove substring of buf to output (line)
**	memmove chunk after nl to start of buf (overwrite read chunk!)
**	bzero / delete buffer when no more lines to write out
*/
