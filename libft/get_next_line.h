/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbehra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/10 13:26:34 by tbehra            #+#    #+#             */
/*   Updated: 2018/05/23 19:07:29 by tbehra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <stdlib.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <unistd.h>
# include "libft.h"
# define GNL_BUFF_SIZE 1024
# define UNDEF -99

typedef	struct				s_line_reader
{
	int						str_i;
	int						ret_read;
	int						fd;
	char					*str;
	struct s_line_reader	*next;
}							t_line_reader;

int							read_in_str(t_line_reader *reader);
int							set_line(int len_line, t_line_reader
								*reader, char **line);
int							get_next_line(const int fd, char **line);
t_line_reader				*init_reader_str(t_line_reader *reader, int fd);

#endif
