/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusengok <yusengok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 13:07:25 by yusengok          #+#    #+#             */
/*   Updated: 2023/12/14 13:55:38 by yusengok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	unsigned char	*ptr;
	size_t			i;

	if (nmemb * size > INT_MAX || ((int)nmemb < 0 && (int)size < 0))
		return (NULL);
	ptr = malloc(nmemb * size);
	if (!ptr)
		return (NULL);
	i = 0;
	while (i < nmemb * size)
		ptr[i++] = 0;
	return (ptr);
}

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*last;

	if (!lst)
		return (NULL);
	last = lst;
	while (last->next)
	{
		last = last->next;
	}
	return (last);
}

int	ft_found_newline(t_list *stash)
{
	int		i;
	t_list	*last_node;

	if (!stash)
		return (0);
	last_node = ft_lstlast(stash);
	i = 0;
	while (last_node->content[i])
	{
		if (last_node->content[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

int	ft_get_char_count(t_list *stash)
{
	int	count;
	int	i;

	if (!stash)
		return (0);
	count = 0;
	while (stash)
	{
		i = 0;
		while (stash->content[i])
		{
			if (stash->content[i] == '\n')
			{
				count++;
				return (count);
			}
			count++;
			i++;
		}
		stash = stash->next;
	}
	return (count);
}

/// To create a new function from two
void	ft_clear_list(t_list **lst)
{
	t_list	*tmp;

	if (!lst || !del)
		return ;
	while (*lst)
	{
		tmp = (*lst)->next;
		ft_lstdelone(*lst, del);
		*lst = tmp;
	}
	free(*lst);
	*lst = NULL;
}

void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	if (!lst || !del)
		return ;
	del(lst->content);
	free(lst);
}
/*

char	*ft_initialize_buf(size_t buf_size, size_t size)
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

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	if (s)
	{
		while (s[i])
			i++;
	}
	return (i);
}

char	*ft_strchr(const char *s, int c)
{
	unsigned int	i;

	i = 0;
	if (s)
	{
		while (s[i])
		{
			if (s[i] == (char)c)
				return ((char *)&s[i]);
			i++;
		}
		if (s[i] == (char)c)
			return ((char *)&s[i]);
	}
	return (NULL);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char			*res;
	unsigned int	res_len;
	unsigned int	i;
	unsigned int	j;

	res_len = ft_strlen((char *)s1) + ft_strlen((char *)s2);
	res = (char *)malloc((res_len + 1) * sizeof(char));
	if (!res)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[i])
		res[j++] = s1[i++];
	i = 0;
	while (s2[i])
		res[j++] = s2[i++];
	res[j] = '\0';
	return (res);
}

char	*ft_strdup(const char *s)
{
	char	*copy;
	int		i;

	copy = (char *)malloc(sizeof(char) * (ft_strlen((char *)s) + 1));
	if (copy == NULL)
		return (NULL);
	i = 0;
	while (s[i])
	{
		copy[i] = s[i];
		i++;
	}
	copy[i] = '\0';
	return (copy);
}

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char		*dest_ptr;
	const char	*src_ptr;
	size_t		i;

	if (!dest && !src)
		return (dest);
	dest_ptr = (char *)dest;
	src_ptr = (const char *)src;
	i = 0;
	if (dest_ptr > src_ptr)
	{
		while (n-- > 0)
			dest_ptr[n] = src_ptr[n];
	}
	else
	{
		while (i < n)
		{
			dest_ptr[i] = src_ptr[i];
			i++;
		}
	}
	return (dest);
}
*/

// char	*ft_substr(char const *s, unsigned int start, size_t len)
// {
// 	char	*substring;
// 	size_t	i;
// 	size_t	s_len;

// 	if (!s)
// 		return (NULL);
// 	s_len = ft_strlen((char *)s);
// 	if (start > s_len)
// 		return (ft_strdup(""));
// 	if (start + len > s_len)
// 		len = s_len - start;
// 	substring = malloc((len + 1) * sizeof(char));
// 	if (!substring)
// 		return (NULL);
// 	i = 0;
// 	while (i < len)
// 	{
// 		substring[i] = s[start + i];
// 		i++;
// 	}
// 	substring[i] = '\0';
// 	return (substring);
// }
