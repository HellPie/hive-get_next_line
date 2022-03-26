/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drossi <drossi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 19:20:01 by drossi            #+#    #+#             */
/*   Updated: 2022/03/26 01:15:00 by drossi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "ft_string.h"
#include "ft_extra.h"
#include "ft_span.h"
#include "get_next_line.h"

static t_bool	_read_fd(int fd, t_span *span, ssize_t *s_out)
{
	*s_out = -1;
	if (span->s_data - span->len < BUFF_SIZE)
		if (!ft_span_res(span, span->s_data + BUFF_SIZE))
			return (FALSE);
	*s_out = read(fd, span->data + span->len, BUFF_SIZE);
	return (*s_out > 0);
}

static int	_proc_ret(char **out, t_span *span, ssize_t s_read, char *endl)
{
	size_t	len;

	if (s_read < 0 || (!s_read && !span->data))
	{
		ft_span_del(span);
		return (s_read);
	}
	len = span->len;
	if (endl)
		len = endl - (char *)span->data;
	*out = ft_strsub(span->data, 0, len);
	if (!*out)
	{
		ft_span_del(span);
		return (GNL_ERR);
	}
	if (span->len <= len)
	{
		ft_bzero(span->data, span->s_data);
		span->len = 0;
		return (GNL_OK);
	}
	ft_memcpy(span->data, (char *)span->data + len + 1, span->len -= len + 1);
	return (GNL_OK);
}

int	get_next_line(const int fd, char **line)
{
	static t_span	fds[GNL_FD_MAX];
	char			*endl;
	ssize_t			s_read;

	if (fd < 0 || fd >= GNL_FD_MAX || read(fd, NULL, 0)
		|| (!fds[fd].data && !ft_span_new(&fds[fd], BUFF_SIZE, sizeof(char))))
		return (GNL_ERR);
	endl = ft_memchr(fds[fd].data, '\n', fds[fd].len);
	if (endl)
		return (_proc_ret(line, &fds[fd], 1, endl));
	while (!endl && _read_fd(fd, &fds[fd], &s_read) > 0)
	{
		endl = ft_memchr(fds[fd].data + fds[fd].len, '\n', (size_t)s_read);
		fds[fd].len += (size_t)s_read;
	}
	return (_proc_ret(line, &fds[fd], s_read, endl));
}
