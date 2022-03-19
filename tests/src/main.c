/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drossi <drossi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 22:50:11 by drossi            #+#    #+#             */
/*   Updated: 2022/02/21 16:42:47 by drossi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include "get_next_line.h"

static int	_proc_stdio(void)
{
	char	*line;
	int		result;

	while (1)
	{
		result = get_next_line(0, &line);
		if (result == 1)
			printf("[  OK  ] Desc: STDIN, Line: \"%s\"", line);
		else if (result == 0)
			printf("[ DONE ] Desc: STDIN, Line: \"%s\"", line);
		else
			printf("[ WARN ] Desc: STDIN, Line: \"%s\"", line);
		if (result != 1)
			return (result);
	}
}

static int	_proc_files(char **fnames, int count)
{
	int		i_fds;
	int		fds[1024];
	char	*line;
	int		result;

	i_fds = 0;
	while (i_fds < count)
		fds[i_fds] = open(fnames[i_fds], O_RDONLY);
	i_fds = 0;
	while (i_fds < count)
	{
		result = get_next_line(fds[i_fds++], &line);
		if (result == 1)
			printf("[  OK  ] Desc: %5d, Line: \"%s\"", fds[i_fds], line);
		else if (result == 0)
			printf("[ DONE ] Desc: %5d, Line: \"%s\"", fds[i_fds], line);
		else
			printf("[ WARN ] Desc: %5d, Line: \"%s\"", fds[i_fds], line);
		free(line);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	if (argc < 2)
	{
		return (_proc_stdio());
	}
	else
	{
		return (_proc_files(&argv[1], argc - 1));
	}
}
