/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main-multiple.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drossi <drossi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 16:52:48 by drossi            #+#    #+#             */
/*   Updated: 2022/03/28 19:30:06 by drossi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include "ft_defs.h"
#include "get_next_line.h"

static int	_process(int r_fd, int w_fd)
{
	//
}

void	_init(int *r_fds, int *w_fds, int *out)
{
	r_fds[0] = open("./assets/multiple/1.in", O_RDONLY);
	r_fds[1] = open("./assets/multiple/2.in", O_RDONLY);
	r_fds[2] = open("./assets/multiple/3.in", O_RDONLY);
	w_fds[0] = open("./assets/multiple/1.out", O_CREAT | O_TRUNC | O_RDWR, 666);
	w_fds[1] = open("./assets/multiple/2.out", O_CREAT | O_TRUNC | O_RDWR, 666);
	w_fds[2] = open("./assets/multiple/3.out", O_CREAT | O_TRUNC | O_RDWR, 666);
	out[0] = 1;
	out[1] = 1;
	out[2] = 1;
}

int	main(void)
{
	int	r_fds[3];
	int	w_fds[3];
	int	out[3];
	int	index;

	while (out[0] == 1 || out[1] == 1 || out[2] == 1)
	{
		index = -1;
		while (++index < 3)
		{
			if (out[index])
			{
				out[index] = _process(r_fds[index], w_fds[index]);
				if (out[index] == GNL_ERR)
					write(w_fds[index], "---ERR---", 9);
			}
		}
	}
}
