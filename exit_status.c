# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <string.h>
# include <unistd.h>
# include <sys/wait.h>
# include <limits.h>
# include <fcntl.h>
# include <errno.h>
# include "libft/libft.h"

int	func()
{
	printf("14: %d\n", errno);
	open("xxxxx", R_OK);
	printf("15: %d\n", errno);
	perror("xxxxx");
	return (-1);
}

int	main(void)
{
	func();
	printf("21: %d\n", errno);
	exit(256);
	return (errno);
}
