#include "get_next_line.h"
#include <fcntl.h>

int	main(void)
{
	int		fd1;
	char	*line1;
	int		fd2;
	char	*line2;

	fd1 = open("file1", O_RDONLY);
	if (fd1 < 0)
		return (1);
	while ((line1 = get_next_line(fd1)) != NULL)
	{
		printf("LINE = %s", line1);
		free(line1);
	}
	close(fd1);
	printf("\n");
	fd2 = open("file2", O_RDONLY);
	if (fd2 < 0)
		return (1);
	while ((line2 = get_next_line(fd2)) != NULL)
	{
		printf("LINE = %s", line2);
		free(line2);
	}
	close(fd2);
	return (0);
}

// #include "get_next_line_bonus.h"

// int main(void)
// {
//     int fd1, fd2;
//     char *line;

//     fd1 = open("file1.txt", O_RDONLY);
//     fd2 = open("file2.txt", O_RDONLY);

//     if (fd1 < 0 || fd2 < 0)
//     {
//         perror("open");
//         return (1);
//     }

//     printf("---- Reading alternately ----\n");
//     line = get_next_line(fd1);
//     printf("fd1: %s", line);
//     free(line);

//     line = get_next_line(fd2);
//     printf("fd2: %s", line);
//     free(line);

//     line = get_next_line(fd1);
//     printf("fd1: %s", line);
//     free(line);

//     line = get_next_line(fd2);
//     printf("fd2: %s", line);
//     free(line);

//     printf("---- Reading file1 completely ----\n");
//     while ((line = get_next_line(fd1)))
//     {
//         printf("fd1: %s", line);
//         free(line);
//     }

//     printf("---- Reading file2 completely ----\n");
//     while ((line = get_next_line(fd2)))
//     {
//         printf("fd2: %s", line);
//         free(line);
//     }

//     close(fd1);
//     close(fd2);
//     return (0);
// }
