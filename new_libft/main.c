#include "libft.h"
#include <stdio.h>


int main(void)
{
	char *line;

	while (1)
	{
		line = get_next_line(STDIN_FILENO);
		if (!line)
			break;
		printf("%s\n", line);
		free(line);
	}
	printf("I am done\n");
	return (0);
}
