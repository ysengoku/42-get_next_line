/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusengok <yusengok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 13:07:28 by yusengok          #+#    #+#             */
/*   Updated: 2023/12/20 18:17:19 by yusengok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_store_buf(int fd, char *stash);
static char	*ft_append_buf(char *stash, char *buf);
static char	*ft_truncate_line(char *line);

char	*get_next_line(int fd)
{
	static char	*stash = NULL;
	char		*line;

	if (fd < 0 || BUFFER_SIZE < 1 || read(fd, 0, 0) < 0)
	{
		free(stash);
		stash = NULL;
		return (NULL);
	}
	line = ft_store_buf(fd, stash);
	if (!line)
		return (NULL);
	stash = ft_truncate_line(line);
	return (line);
}

static char	*ft_store_buf(int fd, char *stash)
{
	char	*buf;
	ssize_t	read_size;

	read_size = 1;
	buf = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buf)
		return (NULL);
	while (read_size > 0)
	{
		read_size = read(fd, buf, BUFFER_SIZE);
		buf[read_size] = '\0';
		if (read_size == 0 || read_size == -1)
			break ;
		stash = ft_append_buf(stash, buf);
		if (!stash)
			break ;
		if (ft_strchr(buf, '\n'))
			break ;
	}
	free(buf);
	buf = NULL;
	return (stash);	
}

static char	*ft_append_buf(char *stash, char *buf)
{
	char	*tmp;

	if (!stash)
	{
		stash = ft_strdup("");
		if (!stash)
			return (NULL);
	}
	tmp = stash;
	stash = ft_strjoin(tmp, buf);
	free(tmp);
	tmp = NULL;
	if (!stash)
		return (NULL);
	return (stash);
}

static char	*ft_truncate_line(char *line)
{
	ssize_t	i;
	char	*tmp;

	i = 0;
	while (line[i] != '\n' && line[i] != '\0')
		i++;
	//--- Here, line[i] is \n or \0. 
	//--- We check line[i] in case there is no \n, line[i+1] in case line[i] is \n.
	if (line[i] == '\0' || line[i + 1] == '\0')
		return (NULL);
	tmp = ft_substr(line, i + 1, ft_strlen(line) - i);
	if (!tmp)
	{
		line = NULL;
		return (NULL);
	}
	line[i + 1] = '\0';
	return (tmp);
}
