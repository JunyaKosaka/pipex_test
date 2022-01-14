#include "pipex.h"

/*   return 1   */
int	error_handler(void)
{
	ft_putstr_fd("Error\n", STDERR);
	return (1);
}
