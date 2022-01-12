#include "pipex.h"

static int	get_filefd(t_info *info, int i)
{
	int	fd;

	if (info->file && i == 2)
	{
		if (!is_valid_file(*info)) // 子プロセスでやるべきかも？
		{
			ft_putstr_fd("pipex: ", 2);
			perror(info->argv[1]);
			info->error_status = errno;
		}
		// is_valid_file();
		fd = open(info->file, R_OK);
	}
	else if (info->file && i + 2 == info->argc)
	{
		if (info->is_here_doc == false)
		{
			unlink(info->file);
			fd = open(info->file, O_CREAT | W_OK, 0644);
		}
		else
			fd = open(info->file, O_APPEND | W_OK | O_CREAT, 0644);
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
	int	total_len;

	if (info.is_here_doc == true && i == 2)
	{
		total_len = ft_strlen(info.total_document);
		close(info.pipefd[0][0]);
		write(info.pipefd[0][1], info.total_document, total_len);
		close(info.pipefd[0][1]);
		exit(0);
	}
	filefd = get_filefd(&info, i);
	if (filefd == -1)
		exit(1); //エラー文　mallocリークチェック
	dup2_func(info, filefd, i);
	close_func(info, filefd, i);
	fprintf(stderr, "errno: %d\n", errno);
	execve(info.cmd_full_path, info.cmd, info.envp);
	// ft_putendl_fd("pipex: illegal option", 2);
	exit(127);
}

static void	set_elements(t_info *info, int i)
{
	info->file = NULL;
	if (i == 2 && !info->is_here_doc)
		info->file = info->argv[i - 1];
	else if (i + 2 == info->argc)
		info->file = info->argv[i + 1];
	if (!(info->is_here_doc && i == 2))
	{
		info->cmd = ft_split(info->argv[i], ' ');
		convert_to_cmd_full_path(info);
	}
}

int	start_process(t_info info)
{
	int	wstatus;
	int	i;

	i = 2;
	while (i + 1 < info.argc)
	{

		set_elements(&info, i);
		if (pipe(info.pipefd[i - 2]) < 0)
		{
			perror("pipe");
			exit(-1);
		}
		info.pid[i - 2] = fork();
		if (info.pid[i - 2] == 0)
			{
				child_exe(info, i);
			}
		else
		{
			if (i != 2)
			{
				close(info.pipefd[i - 3][0]);
				close(info.pipefd[i - 3][1]);
			}
		}
		i++;
	}
	i = 0;
	while (i < info.argc - 3 - info.is_here_doc)
	{
		int	res = waitpid(info.pid[i], &wstatus, WUNTRACED);
		printf("125: %d %d\n", res, wstatus);
		printf("127: %d %d %d\n", i, WIFEXITED(wstatus), WEXITSTATUS(wstatus));
		if (res == -1)
		{
			exit(errno);// だめそう
		}
		i++;
	}
	printf("\n");
	// exit(info.error_status);
	// exit(wstatus);  // 終了ステータス
	return (WEXITSTATUS(wstatus));
}



