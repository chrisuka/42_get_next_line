/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikarjala <ikarjala@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 17:45:37 by ikarjala          #+#    #+#             */
/*   Updated: 2022/02/21 21:18:26 by ikarjala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	get_next_line(const int fd, char **line)
{
	static char	buf[BUFF_SIZE + 1];
	ssize_t		rbytes;
	size_t		tailbs;
	char		*p_nl;
	char		*trash;

	if (!line || fd < 0)
		return (RET_ERROR);
	buf[BUFF_SIZE] = 0;
	ft_strdel(line);
	p_nl = NULL;
	while (!p_nl)
	{
		p_nl = ft_strchr(buf, '\n');
		if (p_nl)
			*p_nl++ = 0;
		trash = *line;
		if (!*line)
			*line = ft_strdup(buf);
		else
			*line = ft_strjoin(*line, buf);
		ft_strdel(&trash);
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
	tailbs = (size_t)(&buf[BUFF_SIZE + 1] - p_nl);
	ft_memmove(buf, p_nl, tailbs);
	buf[tailbs] = 0;
	return (RET_READL);
}

// TODO: t_list structure for buffers
// content[BUFF_SIZE], bookmark
// lst_to_str function (join all buffers into 1 str upon finding nl)
