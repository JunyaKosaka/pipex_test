#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <string.h>
# include <unistd.h>
# include <sys/wait.h>
# include <limits.h>
# include <fcntl.h>
# include "libft/libft.h"

# include <errno.h>
# include <sys/types.h>
# include <sys/uio.h>

# define STDIN 0
# define STDOUT 1
# define STDERR 2
# define NOFILE -2
# define FD_MAX 256

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 256
# endif

typedef struct s_info
{
	int		**pipefd;
	int		argc;
	char	**argv;
	char	**envp;
	char	*cmd_full_path;
	char	**cmd;
	char	*file;
	bool	is_here_doc;
	char	*total_document;
	char	*limiter;
	pid_t	*pid;
	int		error_status;
}	t_info;

bool	is_valid_file(t_info info);
bool	is_valid_cmds(t_info info);
void	convert_to_cmd_full_path(t_info *info);
char	*get_next_line(int fd);
void	*free_one(char **s);
void	*free_all(char **s1, char **s2);
int		start_process(t_info info);
int		error_handler(void);

#endif


