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

void	convert_to_cmd_full_path(t_info *info)
{
	char	**all_paths;
	int		e_index;
	int		c_index;

	if (!access(info->cmd[0], R_OK))
	{
		info->cmd_full_path = info->cmd[0];
		printf("full path input[%s]\n", info->cmd_full_path);
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
			printf("relative path [%s]\n", info->cmd_full_path);
			return ;
		}
		c_index++;
	}
	exit(1);
}

// int    start_process(t_info info)
// {
//    int    wstatus;

//    printf("%d:%d\n", info.pipefd[0], info.pipefd[1]);
//    info.pid = fork();

//    if (info.pid == 0)
//    {
//        close(info.pipefd[0]);
// 		int file_fd = open(info.argv[1], R_OK);
// 		if (file_fd < 0)
// 			printf("open error\n");
// 		dup2(file_fd, 0);
//        dup2(info.pipefd[1], 1);
// 		close(info.pipefd[1]);
// 		// ls -> /bin/ls に変更
//        execve(info.cmd_full_path, info.cmd, info.envp);
// 		// pipeに情報が書き込まれている
//    }
//    else
//    {
//        waitpid(info.pid, &wstatus, WUNTRACED);
//       close(info.pipefd[1]);
//       char *cmd[4];
//        cmd[0] = "/usr/bin/head";
//        cmd[1] = "-n";
//        cmd[2] = "3";
//        cmd[3] = NULL;
//        dup2(info.pipefd[0], 0);
// 		dup2(info.pipefd[1], 1);
// 		close(info.pipefd[0]);
// 		printf("50\n");
// 		// 多分 fork();
//        execve("/usr/bin/head", cmd, info.envp);
//    }
//    return (0);
// }


// void	child_exe2(t_info info)
// {
// 	// int fd;

// 	// fd = open(info.file, R_OK);
// 	// printf("%s\n", info.file);
// 	dup2(info.pipefd[0], 0);
// 	// dup2(info.pipefd[1], 1);
// 	      char *cmd[4];
//        cmd[0] = "/usr/bin/head";
//        cmd[1] = "-n";
//        cmd[2] = "4";
//        cmd[3] = NULL;
// 	printf("chile2\n");
// 	execve("/usr/bin/head", cmd, info.envp);
// 	printf("exe_error\n");
// 	return ;
// }

void	child_exe(t_info info, int i)
{
	int input_fd;
	int	output_fd;

	input_fd = 0;
	output_fd = 1;
	if (info.file != NULL && i == 2)
	{
		input_fd = open(info.file, R_OK);
		fprintf(stderr, "input_fd%d\n", input_fd);
		dup2(input_fd, 0);
		dup2(info.pipefd[i - 2][1], 1);
		close(input_fd);
		close(info.pipefd[i - 2][0]);
		close(info.pipefd[i - 2][1]);
	}
	else if (info.file != NULL && i + 2 == info.argc)
	{
		output_fd = open(info.file, W_OK);
		fprintf(stderr, "%d\n", output_fd);

		fprintf(stderr, "hello\n");
		dup2(output_fd, 1);
		dup2(info.pipefd[i - 2][0], 0);
		close(output_fd);
		close(info.pipefd[i - 2][0]);
		close(info.pipefd[i - 2][1]);
	}
	else
	{
		dup2(info.pipefd[i - 2][0], 0);
		dup2(info.pipefd[i - 1][1], 1);
		close(info.pipefd[i - 2][0]);
		close(info.pipefd[i - 1][1]);
	}

	// exit(0);
	execve(info.cmd_full_path, info.cmd, info.envp);
	fprintf(stderr, "exe_error\n");
	return ;
}

void	start_process(t_info info)
{
	int	wstatus;
	int	fd;
	int	i;
	int j; //消す

	i = 2;
	while (i + 1 < info.argc)
	{
		fprintf(stderr, "%d:%d\n", i, info.argc);
		if (i == 2)
		{
			info.cmd = ft_split(info.argv[i], ' ');
			info.file = info.argv[i - 1];
		}
		else if (i + 2 == info.argc)
		{
			printf("running\n");
			info.cmd = ft_split(info.argv[i], ' ');
			info.file = info.argv[i + 1];
		}
		else
		{
			info.cmd = ft_split(info.argv[i], ' ');
			info.file = NULL;
		}
		convert_to_cmd_full_path(&info);
		j = 0;
		printf("filename:%s\n", info.file);
		printf("command elements");
		while (info.cmd[j] != NULL)
			printf("[%s]", info.cmd[j++]);
		printf("\n");

		pipe(info.pipefd[i - 2]);
		info.pid = fork();
		if (info.pid == 0)
			child_exe(info, i);
		else
			waitpid(info.pid, &wstatus, WUNTRACED);
		i++;
	}
	exit(0);
}

int    main(int argc, char **argv, char **envp)
{
    t_info    info;
	int			i;

	// i = 2;
	// info.cmd = ft_split(info.argv[2], ' ');
	// info.file = info.argv[1];
	// printf("command element:[%s][%s]\n", info.cmd[0], info.cmd[1]);
	// convert_to_cmd_full_path(&info);
	i = 0;
	printf("%p\n", &envp);
	printf("%p\n", &i);
    info.argv = argv;
	info.argc = argc;
    info.envp = envp;
	// if (pipe(info.pipefd) < 0)
	// {
	// 	perror("pipe");
	// 	exit(-1);
	// }
	start_process(info);

    exit(0);
}
