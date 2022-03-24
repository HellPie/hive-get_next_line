/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drossi <drossi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 19:20:01 by drossi            #+#    #+#             */
/*   Updated: 2022/03/24 19:39:56 by drossi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "ft_string.h"
#include "ft_extra.h"
#include "ft_span.h"
#include "get_next_line.h"

static ssize_t	_read_fd(int fd, t_span *span, ssize_t *out_s_read)
{
	if (span->s_data - span->len < BUFF_SIZE
		&& !ft_span_res(span, span->s_data + BUFF_SIZE))
		return (*out_s_read = -1);
	return (*out_s_read = read(fd, span->data + span->len, BUFF_SIZE));
}

static int	_crop_str(char **out, t_span *span, size_t len)
{
	*out = ft_strsub(span->data, 0, len);
	if (!*out)
	{
		ft_span_del(span);
		return (GNL_ERR);
	}
	if (span->len == len)
	{
		span->len = 0;
		return (GNL_OK);
	}
	span->len -= len + 1;
	ft_memcpy(span->data, span->data + len + 1, span->len);
	return (GNL_OK);
}

int	get_next_line(const int fd, char **line)
{
	static t_span	fds[GNL_FD_MAX];
	char			*endl;
	ssize_t			s_read;

	if (fd < 0 || fd >= GNL_FD_MAX || !line || read(fd, NULL, 0)
		|| (!fds[fd].data && !ft_span_new(&fds[fd], BUFF_SIZE, sizeof(char))))
		return (GNL_ERR);
	s_read = 1;
	endl = ft_memchr(fds[fd].data, '\n', fds[fd].len);
	while (!endl && _read_fd(fd, &fds[fd], &s_read) > 0)
	{
		endl = ft_memchr(fds[fd].data + fds[fd].len, '\n', (size_t)s_read);
		fds[fd].len += (size_t)s_read;
	}
	if (s_read < 0 || (!s_read && !fds[fd].len))
	{
		ft_span_del(&fds[fd]);
		return (s_read);
	}
	if (endl)
		return (_crop_str(line, &fds[fd], endl - (char *)fds[fd].data));
	return (_crop_str(line, &fds[fd], fds[fd].len));
}
