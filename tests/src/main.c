/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drossi <drossi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 22:50:11 by drossi            #+#    #+#             */
/*   Updated: 2022/03/27 19:30:24 by drossi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include "get_next_line.h"

int	main(int argc, char **argv)
{
	int		fd;
	int		out;
	char	*line;

	if (argc < 1)
		return (0);
	fd = open(argv[1], O_RDONLY);
	out = 1;
	while (out == 1)
	{
		out = get_next_line(fd, &line);
		if (line)
		{
			printf("%s\n", line);
			free(line);
			line = NULL;
		}
		else
			printf("---ERROR--- LINE IS NULL ---ERROR---\n");
	}
	if (out == 0)
		printf("---END--- REACHED EOF ---END---\n");
	else
		printf("---END--- ERROR: %d ---END---\n", out);
	return (0);
}
