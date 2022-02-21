/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikarjala <ikarjala@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 17:46:50 by ikarjala          #+#    #+#             */
/*   Updated: 2022/02/21 20:48:47 by ikarjala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include "libft.h"

# define RET_READL	1
# define RET_EOF	0
# define RET_ERROR	-1

# define BUFF_SIZE	256
# define FD_MAX		8192

int	get_next_line(const int fd, char **line);

#endif
