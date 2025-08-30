#include <fcntl.h>
#include "get_next_line.h"

int main()
{
	int fd1;
	char *line1;
	int fd2;
	char *line2;

	fd1 = open("file1", O_RDONLY);
	if (fd1 < 0)
		return (1);
	while ((line1 = get_next_line(fd1)) != NULL)
	{
		printf("LINE = %s", line1);
		free(line1);
	}
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