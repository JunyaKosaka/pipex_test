#ifndef PIPEX_H
# define PIPEX_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include "libft/libft.h"

typedef struct s_info
{
	int		pipefd[2];
	int		argc;
	char	**argv;	
	char	**envp;
	pid_t	pid;
}	t_info;

bool	is_valid_file(t_info info);
bool	is_valid_cmds(t_info info);

#endif
