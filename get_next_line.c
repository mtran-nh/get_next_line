/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtran-nh <mtran-nh@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 17:04:53 by mtran-nh          #+#    #+#             */
/*   Updated: 2025/07/28 14:07:11 by mtran-nh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*init_remain(char *remain)
{
	if (remain)
		return (remain);
	return (ft_strdup(""));
}

char	*read_until_nextline(int fd, char *remain)
{
	char	*buffer;
	int		read_bytes;
	char	*temp;

	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	remain = init_remain(remain);
	if (!remain)
		return (NULL);
	read_bytes = 1;
	while (!ft_strchr(remain, '\n') && read_bytes != 0)
	{
		read_bytes = read(fd, buffer, BUFFER_SIZE);
		if (read_bytes == -1)
			return (free(buffer), free(remain), NULL);
		buffer[read_bytes] = '\0';
		temp = remain;
		remain = ft_strjoin(temp, buffer);
		free(temp);
		if (!remain)
			return (free(buffer), NULL);
	}
	return (free(buffer), remain);
}

char	*write_line(char *remain)
{
	char	*line;
	int		i;

	if (!remain || remain[0] == '\0')
		return (NULL);
	i = 0;
	while (remain[i] && remain[i] != '\n')
		i++;
	if (remain[i] == '\n')
		i++;
	line = malloc(i + 1);
	if (!line)
		return (NULL);
	i = 0;
	while (remain[i] && remain[i] != '\n')
	{
		line[i] = remain[i];
		i++;
	}
	if (remain[i] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	return (line);
}

char	*new_remain(char *remain)
{
	int		i;
	int		j;
	char	*new_remain;

	i = 0;
	j = 0;
	if (!remain)
		return (NULL);
	while (remain[i] && remain[i] != '\n')
		i++;
	if (!remain[i])
		return (free(remain), NULL);
	i++;
	new_remain = malloc(ft_strlen(remain + i) + 1);
	if (!new_remain)
		return (free(remain), NULL);
	while (remain[i])
		new_remain[j++] = remain[i++];
	new_remain[j] = '\0';
	return (free(remain), new_remain);
}

char	*get_next_line(int fd)
{
	static char	*remain;
	char		*next_line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	remain = read_until_nextline(fd, remain);
	if (!remain)
		return (NULL);
	next_line = write_line(remain);
	if (!next_line)
	{
		free(remain);
		remain = NULL;
		return (NULL);
	}
	remain = new_remain(remain);
	return (next_line);
}
