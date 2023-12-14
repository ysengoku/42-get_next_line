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

static void	ft_store_buf(int fd, t_list **stash);
static void	ft_add_to_list(t_list **stash, char *buf);
static char	*ft_fetch_line(t_list *stash);
static void	ft_clean_stash(t_list *stash);

char	*get_next_line(int fd)
{
	static t_list	*stash = NULL;
	char			*line;
	
	if (fd < 0 || BUFFER_SIZE < 1 || read(fd, &line, 0) < 0)
		return (NULL);
	line = NULL;
// ------ Read & store in line
	ft_store_buf(fd, stash);
	if (!line)
	{
		free(line);
		return (NULL);
	}
// ------ Fetch line
	line = ft_fetch_line(stash);
// ------ Clean up the stash
	ft_clean_stash(stash);
	return (line);
}

static void	ft_store_buf(int fd, t_list **stash)
{
	char	*buf;
	ssize_t	read_size;

	read_size = 1;
	while (!ft_found_newline(*stash) && read_size > 0)
	{
		buf = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
//		buf = ft_initialize_buf(BUFFER_SIZE, sizeof(char));
//		buf = malloc((BUFFER_SIZE + 1) * sizeof(char));
		if (!buf)
			return ;
		read_size = read(fd, buf, BUFFER_SIZE);
		if (read_size == 0 ||read_size == -1)
		{
			free(buf);
			return ;
		}
//		buf[read_size] = '\0';
		ft_add_to_list(stash, buf);
		free(buf);
	}
}

static void	ft_add_to_list(t_list *stash, char *buf)
{
	t_list	*last_node;
	t_list	*new_node;
	int		i;

	last_node = ft_lstlast(*stash);
	new_node = (t_list *)malloc(sizeof(t_list));
	if (!new_node)
		return ;
	new_node->next = NULL;
	new_node->content = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!new_node->content)
		return ;
	i = 0;
	while (buf[i++])
		new_node->content[i - 1] = buf[i - 1];
	new_node->content[i] = '\0';
	if (!last_node)
		stash = new_node;
	else
		last_node->next = new_node;
}

static char	*ft_fetch_line(t_list *stash)
{
	int	len;
	int	i;
	int	j;
	char	*line;

	if (!stash)
		return ;
	i = 0;
	len = ft_get_char_count(stash);
	line = ft_calloc(len + 1, sizeof(char));
	if (!line)
		return (NULL);
	while (stash)
	{
		j = 0;
		while (stash->content[j] && stash->content[j] != '\n')
			line[i++] == stash->content[j++];
		stash = stash->next;
	}
	line[i] = '\0';
	return (line);
}

static void	ft_clean_stash(t_list *stash)
{
	t_list	tmp;
	t_list	last_node;
	int	i;
	int	j;

	last_node = ft_lstlast(stash);
	tmp = malloc(sizeof(t_list));
	if (!tmp)
		return (NULL);

	ft_clear_list(stash);
}
