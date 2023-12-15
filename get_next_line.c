/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusengok <yusengok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 13:07:28 by yusengok          #+#    #+#             */
/*   Updated: 2023/12/14 16:03:50 by yusengok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h> //////////////////////////////////////////////

static char	*ft_initialize_buf(size_t buf_size, size_t size);
static char	*ft_store_buf(int fd, char *stash);
static char	*ft_truncate_line(char *line, char *stash);

char	*get_next_line(int fd)
{
	static char	stash[BUFFER_SIZE + 1];
	char		*line;
	
	if (fd < 0 || BUFFER_SIZE < 1 || read(fd, 0, 0) < 0)
		return (NULL);
	line = ft_store_buf(fd, stash);
	if (!line)
	{
		free(line);
		return (NULL);
	}
// ------ Truncate line & store the remaining in stash
	ft_truncate_line(line, stash);
	return (line);
}

static char	*ft_initialize_buf(size_t buf_size, size_t size)
{
	char	*buf;
	size_t	i;

	buf = malloc((buf_size + 1) * size);
	if (!buf)
		return (NULL);
	i = 0;
	while (i < (buf_size + 1) * size)
		buf[i++] = '\0';
	return (buf);
}

static char	*ft_store_buf(int fd, char *stash)
{
	char	*buf;
	char	*tmp;
	char	*line_buf;
	int		read_size;

	read_size = 1;
	line_buf = ft_strdup(stash);
	while (!ft_strchr(line_buf, '\n') && read_size > 0)
	{
		buf = ft_initialize_buf(BUFFER_SIZE, sizeof(char));
		if (!buf)
			return (NULL);
		tmp = NULL;
		read_size = read(fd, buf, BUFFER_SIZE);
		if (read_size == -1)
			return (free(buf), NULL);
		if (read_size == 0)
			return (free(buf), line_buf);
		tmp = line_buf;
		line_buf = ft_strjoin(tmp, buf);
		free(tmp);
		free(buf);
	}
	return (line_buf);
}

static char	*ft_truncate_line(char *line, char *stash)
{
	int		i;

	i = 0;
//	if (line)
//	{
	while (line[i] != '\n' && line[i] != '\0')
		i++;
	if (line[i] == '\0' || line[i + 1] == '\0')
		return (NULL);
	ft_memmove(stash, &line[i + 1], ft_strlen(line) - i);
	line[i + 1] = '\0';
	return (stash);
//	}
//	free(line);
//	return (NULL);
}
