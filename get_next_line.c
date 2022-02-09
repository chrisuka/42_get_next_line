/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikarjala <ikarjala@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 17:45:37 by ikarjala          #+#    #+#             */
/*   Updated: 2022/02/09 19:01:38 by ikarjala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	get_next_line(const int fd, char **line)
{
	static char	buf[BUFF_SIZE + 1];
	size_t		i_nl;
	ssize_t		bytes;

	if (!fd || !line)
		return (RET_ERROR);
	bytes = 0;
	if (!buf[0])
		bytes = read(fd, buf, BUFF_SIZE);
	if (bytes == 0)
		return (RET_EOF);
	i_nl = (size_t)(ft_strnstr(buf, "\n", BUFF_SIZE) - buf);
	if (*line)
		free(*line);
	*line = ft_strsub(buf, 0, i_nl);
	return (RET_READL);
}
