#include "pipex.h"

static	int	path_index(t_info info)
{
	int	index;

	index = 0;
	while(info.envp[index])
	{
			if(!ft_strncmp(info.envp[index], "PATH=", 5))
					return (index);
			index++;
	}
	return (-1);
}

// info.argv[2] を cmd_full_pathに変更
void	convert_to_cmd_full_path(t_info *info)
{
	char	**all_paths;
	int		e_index;
	int		c_index;

	if (!access(info->cmd[0], R_OK))				
	{
		info->cmd_full_path = info->cmd[0];
		printf("full path input %s\n", info->cmd_full_path);
		return ;
	}
	e_index = path_index(*info);
	if (e_index == -1)
		exit(1);
	all_paths = ft_split(&(info->envp[e_index][5]), ':');
	c_index = 0;
	while (all_paths[c_index])
	{
		
		info->cmd_full_path = ft_strjoin(all_paths[c_index], "/");
		info->cmd_full_path = ft_strjoin(info->cmd_full_path, info->cmd[0]);
		if (!access(info->cmd_full_path, R_OK))				
		{
			printf("relative path %s\n", info->cmd_full_path);
			return ;
		}
		c_index++;
	}
	exit(1);
}

int    start_process(t_info info, int fd)
{
    int    wstatus;

    printf("%d:%d\n", info.pipefd[0], info.pipefd[1]);
    info.pid = fork();

    if (info.pid == 0)
    {
        close(info.pipefd[0]);
		int file_fd = open(info.argv[1], R_OK);
		if (file_fd < 0)
			printf("open error\n");
		dup2(file_fd, 0);
        dup2(info.pipefd[1], 1);
		close(info.pipefd[1]);
		// ls -> /bin/ls に変更
        execve(info.cmd_full_path, info.cmd, info.envp);
		// pipeに情報が書き込まれている
    }
    else
    {
        waitpid(info.pid, &wstatus, WUNTRACED);
        close(info.pipefd[1]);
        //char buf[100000];
        //printf("%s\n", buf);
        //dup2(info.pipefd[])
        char *cmd[4];
        cmd[0] = "/usr/bin/head";
        cmd[1] = "-n";
        cmd[2] = "3";
        cmd[3] = NULL;
        dup2(info.pipefd[0], 0);
		dup2(fd, 1);
		close(info.pipefd[0]);
		printf("50\n");
		// 多分 fork();
        execve("/usr/bin/head", cmd, info.envp);
    }
    return (0);
}

int    main(int argc, char **argv, char **envp)
{
    t_info    info;
    info.argv = argv;
    info.envp = envp;
	int			i;

	i = 2;
	while (i < argc - 1)
	{
		if (i == argc - 2)
		{
			// 終了条件　i == argc - 1 がfile
		}

		i++;
	}
	info.cmd = ft_split(info.argv[2], ' ');
	printf("%s, %s\n", info.cmd[0], info.cmd[1]);
	convert_to_cmd_full_path(&info);
	if (pipe(info.pipefd) < 0)
	{
		perror("pipe");
		exit(-1);
	}
	start_process(info);

    exit(0);
}
