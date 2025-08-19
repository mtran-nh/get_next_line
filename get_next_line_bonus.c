/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtran-nh <mtran-nh@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 21:02:20 by mtran-nh          #+#    #+#             */
/*   Updated: 2025/08/19 16:31:55 by mtran-nh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

void	new_remain(char *remain, char *result)
{
	int	i;
	int	j;

	i = 0;
	if (!remain || !result)
		return ;
	while (result[i] && result[i] != '\n')
		i++;
	if (!result[i] || !result[i + 1])
	{
		remain[0] = '\0';
		return ;
	}
	i++;
	j = 0;
	while (result[i] && j < BUFFER_SIZE)
		remain[j++] = result[i++];
	remain[j] = '\0';
}

static char	*init_remain(char *remain)
{
	if (remain && remain[0] != '\0')
		return (ft_strdup(remain));
	return (ft_strdup(""));
}

static int	check_read(int read_bytes, char *remain, char *buffer, char *result)
{
	if (read_bytes == -1)
	{
		remain[0] = '\0';
		free(buffer);
		free(result);
		return (1);
	}
	return (0);
}

char	*read_until_nextline(int fd, char *remain)
{
	char	*buffer;
	int		read_bytes;
	char	*temp;
	char	*result;

	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	result = init_remain(remain);
	if (!result)
		return (free(buffer), NULL);
	read_bytes = 1;
	while (!ft_strchr(result, '\n') && read_bytes != 0)
	{
		read_bytes = read(fd, buffer, BUFFER_SIZE);
		if (check_read(read_bytes, remain, buffer, result) == 1)
			return (NULL);
		buffer[read_bytes] = '\0';
		temp = result;
		result = ft_strjoin(temp, buffer);
		free(temp);
		if (!result)
			return (free(buffer), NULL);
	}
	return (free(buffer), new_remain(remain, result), result);
}

char	*get_next_line(int fd)
{
	static char	remain[1024][BUFFER_SIZE + 1];
	char		*buffer;
	char		*next_line;

	if (fd < 0 || fd >= 1024 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = read_until_nextline(fd, remain[fd]);
	if (!buffer)
		return (NULL);
	next_line = write_line(buffer);
	if (!next_line)
	{
		free(buffer);
		return (NULL);
	}
	free(buffer);
	return (next_line);
}
