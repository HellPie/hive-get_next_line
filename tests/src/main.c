/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drossi <drossi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 22:50:11 by drossi            #+#    #+#             */
/*   Updated: 2022/03/20 11:53:58 by drossi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include "get_next_line.h"

static char	*_tos(int i)
{
	if (i == GNL_OK)
		return ("[  OK  ] ");
	if (i == GNL_EOF)
		return ("[ DONE ] ");
	if (i == GNL_ERR)
		return ("[ WARN ] ");
	return ("[!ERROR] ");
}

static int	_proc_stdio(void)
{
	char	*line;
	int		result;

	while (1)
	{
		result = get_next_line(0, &line);
		printf("%sFD: STDIN, L: \"%s\"\n", _tos(result), line);
		if (result != 1)
			return (result);
	}
}

static int	_proc_files(int *fds, int count)
{
	int		i_fds;
	char	*line;
	int		result;
	int		completed;

	completed = 0;
	while (completed < count)
	{
		i_fds = -1;
		while (++i_fds < count)
		{
			if (fds[i_fds] < 3 || read(fds[i_fds], NULL, 0))
				continue ;
			result = get_next_line(fds[i_fds], &line);
			printf("%sFD: %2d, L: \"%s\"\n", _tos(result), fds[i_fds], line);
			if (result == 1)
				free(line);
			else
			{
				completed++;
				fds[i_fds] = -1;
			}
		}
	}
	return (0);
}

int	main(int argc, char **argv)
{
	int		fds[GNL_FD_MAX];
	int		i_fds;

	if (argc < 2)
	{
		return (_proc_stdio());
	}
	else
	{
		i_fds = 0;
		while (++i_fds < argc)
			fds[i_fds - 1] = open(argv[i_fds], O_RDONLY);
		return (_proc_files(fds, argc - 1));
	}
}
