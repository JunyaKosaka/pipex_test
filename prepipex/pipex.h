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
	int		pipefd[3][2];
	int		argc;
	char	**argv;
	char	**envp;
	char	*cmd_full_path;
	char	**cmd;
	char	*file;  // in outo
	pid_t	pid;
}	t_info;

bool	is_valid_file(t_info info);
bool	is_valid_cmds(t_info info);

#endif


