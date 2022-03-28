/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drossi <drossi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 16:34:46 by drossi            #+#    #+#             */
/*   Updated: 2022/03/28 16:40:59 by drossi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include "get_next_line.h"

int	main(void)
{
	char	*line;
	int		out;

	out = get_next_line(-1, &line);
	if (out != GNL_ERR)
		return (-1);
	out = get_next_line(10, &line);
	if (out != GNL_ERR)
		return (-1);
	out = get_next_line(GNL_FD_MAX - 1, &line);
	if (out != GNL_ERR)
		return (-1);
	out = get_next_line(GNL_FD_MAX, &line);
	if (out != GNL_ERR)
		return (-1);
	out = get_next_line(GNL_FD_MAX + 1, &line);
	if (out != GNL_ERR)
		return (-1);
	out = get_next_line(GNL_FD_MAX + 2, &line);
	if (out != GNL_ERR)
		return (-1);
	out = get_next_line(INT_MAX, &line);
	if (out != GNL_ERR)
		return (-1);
	return (0);
}
