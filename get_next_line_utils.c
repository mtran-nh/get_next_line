/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtran-nh <mtran-nh@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 17:05:00 by mtran-nh          #+#    #+#             */
/*   Updated: 2025/07/25 17:34:59 by mtran-nh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
		i++;
	return (i);
}

char	*ft_strdup(const char *s)
{
	int		i;
	char	*str;

	if (!s)
		return (NULL);
	str = malloc(ft_strlen(s) + 1);
	if (!str)
		return (NULL);
	i = 0;
	while (s[i])
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	size_t	i;

	if (!s1 || !s2)
		return (NULL);
	str = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!str)
		return (NULL);
	i = 0;
	while (str[i])
	{
		if (i < ft_strlen(s1))
			str[i] = s1[i];
		if (i >= ft_strlen(s1))
			str[i] = s2[i - ft_strlen(s1)];
		i++;
	}
	return (str);
}

char	*ft_strrchr(const char *s, int c)
{
	while (*s != (char)c)
	{
		if (*s == '\0')
			return (NULL);
		s++;
	}
	return ((char *)s);
}

char	*read_until_nextline(int fd, char *remain)
{
	char	*buffer;
	int		read_bytes;

	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	read_bytes = 1;
	while (!ft_strchr(remain, '\n') && read_bytes != 0)
	{
		read_bytes = read(fd, buffer, BUFFER_SIZE);
		if (read_bytes == -1)
		{
			free(buffer);
			return (NULL);
		}
		buffer[read_bytes] = '\0';
		remain = ft_strjoin(remain, buffer);
	}
	free(buffer);
	return (remain);
}

char	*write_line(char *remain)
{
	char	*line;
	int		i;

	i = 0;
	if (!remain)
		return (NULL);
	while (remain[i] && remain[i] != '\n')
		i++;
	line = malloc(i + 2);
	i = 0;
	while (remain[i] && remain[i] != '\n')
	{
		line[i] = remain[i];
		i++;
	}
	if (remain[i] == '\n')
		line[i] = '\n';
	line[i + 1] = '\0';
}

char	*new_remain(char *remain)
{
	int i;
	int j;
	char *new_remain;
	
	i = 0;
	j = 0;
	while(remain[i] && remain[i] != '\n')
		i++;
	if (!remain[i])
		return (NULL);
	new_remain = malloc (ft_strlen(remain + i) + 1);
	if (!new_remain)
		return (NULL);
	i++;
	while (remain[i])
		new_remain[j++] = remain[i++];
	new_remain[j] = '\0';
	return (new_remain);
}
