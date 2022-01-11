#include "pipex.h"

static int	get_filefd(t_info info, int i)
{
	int	fd;

	if (info.file && i == 2)
		fd = open(info.file, R_OK);
	else if (info.file && i + 2 == info.argc)
	{
		unlink(info.file);
		fd = open(info.file, O_CREAT | W_OK, 0644);
	}
	else
		fd = NOFILE;
	return (fd);
}

static void	dup2_func(t_info info, int filefd, int i)
{
	if (filefd != NOFILE && i == 2)
	{
		dup2(filefd, 0);
		dup2(info.pipefd[i - 2][1], 1);
	}
	else if (filefd != NOFILE && i + 2 == info.argc)
	{
		dup2(filefd, 1);
		dup2(info.pipefd[i - 3][0], 0);
	}
	else
	{
		dup2(info.pipefd[i - 3][0], 0);
		dup2(info.pipefd[i - 2][1], 1);
	}
}

static void	close_func(t_info info, int filefd, int i)
{
	if (filefd != NOFILE && i == 2)
		close(info.pipefd[i - 2][0]);
	else if (filefd != NOFILE && i + 2 == info.argc)
		close(info.pipefd[i - 3][1]);
	else
		close(info.pipefd[i - 3][1]);
	if (filefd != NOFILE)
		close(filefd);
	close(info.pipefd[i - 2][1]);
}

static void	child_exe(t_info info, int i)
{
	int	filefd;

	filefd = get_filefd(info, i);
	if (filefd == -1)
		exit(1);
	dup2_func(info, filefd, i);
	close_func(info, filefd, i);
	execve(info.cmd_full_path, info.cmd, info.envp);
	return ;
}

static void	set_elements(t_info *info, int i)
{
	info->file = NULL;
	if (i == 2)
		info->file = info->argv[i - 1];
	else if (i + 2 == info->argc)
		info->file = info->argv[i + 1];
	info->cmd = ft_split(info->argv[i], ' ');
	convert_to_cmd_full_path(info);
}

void	start_process(t_info info)
{
	int	wstatus;
	int	i;

	i = 2;  // here_docの時は i = 3
	while (i + 1 < info.argc)
	{
		set_elements(&info, i);
		if (pipe(info.pipefd[i - 2]) < 0)
		{
			perror("pipe");
			exit(-1);
		}
		info.pid = fork();
		if (info.pid == 0)
			child_exe(info, i);
		else
		{
			if (i != 2)
			{
				close(info.pipefd[i - 3][0]);
				close(info.pipefd[i - 3][1]);
			}
			waitpid(info.pid, &wstatus, WUNTRACED);
		}
		i++;
	}
	exit(0);
}
