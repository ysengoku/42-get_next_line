/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusengok <yusengok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 13:07:28 by yusengok          #+#    #+#             */
/*   Updated: 2023/12/15 15:10:18 by yusengok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h> //////////////////////////////////////////////

static char	*ft_initialize_buf(size_t buf_size, size_t size);
static char	*ft_store_buf(int fd, char *stash);
static void	ft_truncate_line(char *line, char *stash);

char	*get_next_line(int fd)
{
	static char	stash[BUFFER_SIZE + 1];
	char		*line;
	int			i;

	if (fd < 0 || BUFFER_SIZE < 1 || read(fd, &line, 0) < 0)
		return (NULL);
/* ---- read & store buf in line ---- */
	line = ft_store_buf(fd, stash); //---------> line is never NULL
	if (!line)
		return (NULL);
/* ---- clean stash ---- */ 
	i = 0;
	while (stash[i])
		stash[i++] = '\0';
/* ---- truncate line & stock the remaining chars in stash ---- */
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
	char		*buf;
	char		*line;
	char		*tmp;
	ssize_t		read_size;

	read_size = 1;
	tmp = NULL;
	ft_memcpy(tmp, stash, ft_strlen(stash));
	while (read_size > 0)
	{
		buf = ft_initialize_buf(BUFFER_SIZE, sizeof(char));
		if (!buf)
			return (NULL);
		read_size = read(fd, buf, BUFFER_SIZE);
//		if (read_size == -1)
//		 	return (free(buf), NULL);
		if (read_size == 0)
			return (free(buf), line);
		line = ft_strjoin(tmp, buf);
//		if (!line)
//			return (NULL); 	
		free(tmp);
		free(buf);
		if (ft_strchr(line, '\n') != NULL)
			break ;
		ft_memcpy(tmp, line, ft_strlen(line));
	}
	return (line);
}

static void	ft_truncate_line(char *line, char *stash)
{
	int		i;

	i = 0;
	while (line[i] != '\n' && line[i] != '\0')
		i++;
	if (line[i] == '\0' || line[i + 1] == '\0')
		return ;
	ft_memmove(stash, &line[i + 1], ft_strlen(line) - i);
	line[i + 1] = '\0';
}
///// ---------------> issue for /n + EOF && EOF
