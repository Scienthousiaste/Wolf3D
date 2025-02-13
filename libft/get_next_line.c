/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbehra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/16 16:01:31 by tbehra            #+#    #+#             */
/*   Updated: 2018/05/23 19:06:51 by tbehra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int				read_in_str(t_line_reader *reader)
{
	char	*buf;
	char	*new_str;

	if (!(buf = ft_strnew(GNL_BUFF_SIZE)))
		return (-1);
	ft_bzero(buf, GNL_BUFF_SIZE + 1);
	reader->ret_read = read(reader->fd, buf, GNL_BUFF_SIZE);
	if (reader->ret_read == -1 || reader->ret_read == 0)
	{
		free(buf);
		return (reader->ret_read);
	}
	new_str = ft_strjoin(&reader->str[reader->str_i], buf);
	if (!(new_str))
		return (-1);
	reader->str_i = 0;
	free(buf);
	free(reader->str);
	reader->str = new_str;
	return (1);
}

int				set_line(int len_line, t_line_reader *reader, char **line)
{
	int endline;

	if (!(*line = ft_strnew(len_line)))
	{
		*line = NULL;
		return (0);
	}
	ft_strncpy(*line, &reader->str[reader->str_i], len_line);
	endline = (reader->str[reader->str_i + len_line] == '\n') ? 1 : 0;
	reader->str_i += (len_line + endline);
	return (1);
}

int				reread(t_line_reader *reader, int i, char **line)
{
	read_in_str(reader);
	if (reader->ret_read == -1)
		return (-1);
	if (reader->ret_read == 0)
	{
		if (i == 0)
			return (0);
		if (!(set_line(i, reader, line)))
			return (-1);
		return (1);
	}
	return (get_next_line(reader->fd, line));
}

t_line_reader	*init_reader(t_line_reader *first_reader, int fd)
{
	t_line_reader	*new_reader;
	t_line_reader	*next_reader;

	if (fd == -1)
		return (NULL);
	next_reader = first_reader;
	while (next_reader->next != NULL)
	{
		next_reader = next_reader->next;
		if (next_reader->fd == fd)
			return (next_reader);
	}
	if (!(new_reader = (t_line_reader*)malloc(sizeof(t_line_reader))))
		return (NULL);
	if (!(new_reader->str = ft_strnew(0)))
		return (NULL);
	ft_bzero(new_reader->str, 1);
	new_reader->str_i = 0;
	new_reader->ret_read = UNDEF;
	new_reader->fd = fd;
	new_reader->next = NULL;
	if (read_in_str(new_reader) == -1)
		return (NULL);
	next_reader->next = new_reader;
	return (new_reader);
}

int				get_next_line(const int fd, char **line)
{
	int						i;
	t_line_reader			*reader;
	static t_line_reader	first_reader = {0, UNDEF, UNDEF, NULL, NULL};

	if (!line)
		return (-1);
	reader = init_reader(&first_reader, fd);
	if (reader == NULL)
		return (-1);
	i = 0;
	while (reader->str[reader->str_i + i] != '\n'
			&& reader->str[reader->str_i + i] != '\0')
		i++;
	if (reader->str[reader->str_i + i] == '\n')
	{
		if (!(set_line(i, reader, line)))
			return (-1);
		return (1);
	}
	if (reader->str[reader->str_i + i] == '\0')
		return (reread(reader, i, line));
	return (-1);
}
