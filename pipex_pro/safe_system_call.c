#include "pipex.h"

void	safe_func(int res, t_info *info)
{
	if (res == -1)
	{
		free_all_info(info, true);
		exit(1);
	}
}
