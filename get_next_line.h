/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drossi <drossi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 19:19:53 by drossi            #+#    #+#             */
/*   Updated: 2022/03/19 11:28:40 by drossi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFF_SIZE
#  define BUFF_SIZE 8
# endif

# define GNL_FD_MAX 10496

# define GNL_ERR -1
# define GNL_OK 1
# define GNL_EOF 0

int	get_next_line(const int fd, char **line);

#endif
