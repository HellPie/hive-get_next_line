/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drossi <drossi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 19:20:01 by drossi            #+#    #+#             */
/*   Updated: 2022/03/19 22:56:04 by drossi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "ft_string.h"
#include "ft_extra.h"
#include "get_next_line.h"

static t_bool	m_validate(char **buffer, char **line)
{
	char	*found;

	found = ft_strchr(*buffer, '\n');
	if (found == NULL)
		return (FALSE);
	*line = ft_strsub(*buffer, 0, (size_t)(found - *buffer));
	*buffer = ft_strdup(found + 1);
	return (TRUE);
}

static int	m_read(int fd, char *buffer, char **retain, char **line)
{
	int		result;
	char	*copy;

	while (TRUE)
	{
		result = read(fd, buffer, BUFF_SIZE);
		if (result < 1)
			break ;
		buffer[result] = '\0';
		if (*retain)
		{
			copy = *retain;
			*retain = ft_strjoin(*retain, buffer);
			free(copy);
		}
		else
		{
			*retain = ft_strdup(buffer);
		}
		if (m_validate(retain, line))
			break ;
	}
	if (result > 0)
		return (GNL_OK);
	return (result);
}

int	get_next_line(const int fd, char **line)
{
	static char	*retain[GNL_FD_MAX];
	char		*buffer;
	int			result;

	if (!line || fd < 0 || fd >= GNL_FD_MAX || read(fd, NULL, 0) < 0)
		return (GNL_ERR);
	buffer = (char *)ft_memalloc(sizeof(char) * (BUFF_SIZE + 1));
	if (!buffer)
		return (GNL_ERR);
	if (retain[fd] && m_validate(&retain[fd], line))
		return (GNL_OK);
	result = m_read(fd, buffer, &retain[fd], line);
	free(buffer);
	if (result || !retain[fd])
	{
		if (*line && !result)
			*line = NULL;
		return (result);
	}
	*line = retain[fd];
	retain[fd] = NULL;
	return (GNL_EOF);
}
