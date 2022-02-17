/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikarjala <ikarjala@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 17:45:37 by ikarjala          #+#    #+#             */
/*   Updated: 2022/02/17 08:41:32 by ikarjala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	get_next_line(const int fd, char **line)
{
	static char	buf[BUFF_SIZE + 1];
	ssize_t		rbytes;
	char		*p_nl;
	char		*trash;

	if (!fd || !line)
		return (RET_ERROR);
	buf[BUFF_SIZE] = 0;
	while (!p_nl)
	{
		p_nl = ft_strchr(buf, '\n');
		if (p_nl)
			*p_nl++ = 0;
		trash = *line;
		*line = ft_strjoin(*line, buf);
		ft_memdel(&trash);
		if (!*line)
			return (RET_ERROR);
		if (!p_nl)
		{
			rbytes = read(fd, buf, BUFF_SIZE);
			if (!rbytes)
				return (RET_EOF);
			if (rbytes < BUFF_SIZE)
				buf[rbytes] = 0;
		}
	}
	endchunk = (p_nl - buf);
	ft_memmove(buf, p_nl, BUFF_SIZE - p_nl);
	buf[BUFF_SIZE - p_nl] = 0;
	return (RET_READL);
}
