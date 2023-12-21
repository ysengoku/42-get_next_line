/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusengok <yusengok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 16:09:42 by yusengok          #+#    #+#             */
/*   Updated: 2023/12/20 14:29:12 by yusengok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_append_buf(char *stash, char *buf);
//static char	*ft_truncate_line(char *stash, char **line);
static char	*ft_fetch_line(char *stash);
static char	*ft_clean_stash(char *stash);
static void ft_clear_buffer(char **buf);

char	*get_next_line(int fd)
{
	static char	*stash = NULL;
	char		*line;
	ssize_t		read_size;
	char		*buf;

	line = NULL;
	read_size = 1;
	if (fd < 0 || BUFFER_SIZE < 0 || read(fd, 0, 0) < 0)
		return (ft_clear_buffer(&stash), NULL);
	while (read_size > 0)
	{
		buf = malloc((BUFFER_SIZE + 1) * sizeof(char));
		if (!buf)
			return (NULL);
		read_size = read(fd, buf, BUFFER_SIZE);
		if ((read_size < 1 && !stash) || read_size == -1)
			return (ft_clear_buffer(&stash), ft_clear_buffer(&buf), NULL);	
		buf[read_size] = '\0';
		stash = ft_append_buf(stash, buf);
		if (ft_strchr(stash, '\n'))
		{
			line = ft_fetch_line(stash);
			if (!line)
				return (ft_clear_buffer(&stash), ft_clear_buffer(&buf), NULL);
			stash = ft_clean_stash(stash);
			return (line); 
		}
		free(buf);
	}
	line = ft_strdup(stash);
	free(stash);
	stash = NULL;
	return (line);
}

static char	*ft_append_buf(char *stash, char *buf)
{
	char	*tmp;
	char	*result;

	result = 0;
	if (!stash && buf)
	{
		result = ft_strdup(buf);
		if (!result)
			return (ft_clear_buffer(&result), ft_clear_buffer(&buf), NULL);
		return (result);
	}
	tmp = ft_strdup(stash);
	if (!tmp)
	{
		ft_clear_buffer(&stash);
		ft_clear_buffer(&buf);
		return (ft_clear_buffer(&tmp), NULL);
	}
	ft_clear_buffer(&stash);
	result = ft_strjoin(tmp, buf);
	free(tmp);
	if (!result)
	{	
		ft_clear_buffer(&buf);
		free(result);
		result = NULL;
	}
	ft_clear_buffer(&stash);
	return (result);
}

/*
static char	*ft_truncate_line(char *stash, char **line)
{
	ssize_t	i;
	char	*new_stash;

	i = 0;
	while (stash[i] != '\n' && stash[i] != '\0')
		i++;
	if (stash[i] == '\0' || stash[i + 1] == '\0')
		return (NULL);
	new_stash = ft_substr(stash, i + 1, ft_strlen(stash) - i);
	stash[i + 1] = '\0';
	*line = stash;
	return (new_stash);
}
*/

static char	*ft_fetch_line(char *stash)
{
	char	*line;
	size_t	i;
	size_t	j;

	i = 0;
	if (!stash)
		return (ft_clear_buffer(&stash), NULL);
	while (stash[i] != '\n')
		i++;
	line = malloc((i + 2) * sizeof(char));
	if (!line)
		return (ft_clear_buffer(&stash), NULL);
	j = 0;
	while (j < i + 1)
	{
		line[j] = stash[j];
		j++;
	}
	line [j] = '\0';
	return (line);
}

static char	*ft_clean_stash(char *stash)
{
	ssize_t	i;
	char	*new_stash;

	i = 0;
	if (!stash)
		return (NULL);
	while (stash[i] != '\n' && stash[i] != '\0')
		i++;
	if (stash[i] == '\0' || stash[i + 1] == '\0')
		return (ft_clear_buffer(&stash), NULL);
	new_stash = ft_substr(stash, i + 1, ft_strlen(stash) - i);
	if (!new_stash)
		return (ft_clear_buffer(&stash), NULL);
	ft_clear_buffer(&stash);
	return (new_stash);
}

static void ft_clear_buffer(char **buf)
{
	if (!*buf)
		return ;
	free(*buf);
	*buf = NULL;
}
