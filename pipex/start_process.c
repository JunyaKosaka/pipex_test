#include "pipex.h"

static int	get_filefd(t_info *info, int cmd_index)
{
	int	fd;

	if (info->file && cmd_index == 0)
	{
		if (!is_valid_file(*info))
		{
			ft_putstr_fd("pipex: ", STDERR);
			perror(info->argv[1]);
		}
		fd = open(info->file, R_OK);
	}
	else if (info->file && cmd_index + info->first_cmd_index == info->argc - 2)
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

static void	dup2_func(t_info *info, int filefd, int cmd_index) //cmd_index 0~2
{
	if (filefd != NOFILE && cmd_index == 0)
	{
		dup2(filefd, STDIN);
		dup2(info->pipefd[cmd_index][PIPEOUT], STDOUT);
	}
	else if (filefd != NOFILE && cmd_index + info->first_cmd_index == info->argc - 2)// cmd_index=4 process2
	{
		dup2(filefd, STDOUT);
		dup2(info->pipefd[cmd_index - 1][PIPEIN], STDIN);
	}
	else
	{
		dup2(info->pipefd[cmd_index - 1][PIPEIN], STDIN); // cmd_index =3 process1
		dup2(info->pipefd[cmd_index][PIPEOUT], STDOUT);
	}
}

static void	close_func(t_info *info, int filefd, int cmd_index) // cmd_index = 2 3;
{
	if (filefd != NOFILE && cmd_index == 0) // cmd_index=2
		close(info->pipefd[cmd_index][PIPEIN]);
	else if (filefd != NOFILE && cmd_index + info->first_cmd_index == info->argc - 2) // cmd_index =3
		close(info->pipefd[cmd_index - 1][PIPEOUT]);
	else
		close(info->pipefd[cmd_index - 1][PIPEOUT]);
	if (filefd != NOFILE)
		close(filefd);
	if (cmd_index + info->first_cmd_index != info->argc - 2)
		close(info->pipefd[cmd_index][PIPEOUT]); // cmd_index = 2
}

static void	set_elements(t_info *info, int cmd_index)
{
	info->file = NULL;
	if (cmd_index == 0 && !info->is_here_doc)
		info->file = info->argv[1];
	else if (cmd_index  == info->process_cnt - 1)
		info->file = info->argv[info->argc - 1];
	info->cmd[cmd_index] = ft_split(info->argv[info->first_cmd_index + cmd_index], ' ');
	convert_to_cmd_full_path(info, cmd_index);
	// printf("set_element\n");
}

static void	child_exe(t_info *info, int cmd_index) // normal cmd_index = 2 start, here_doc cmd_index = 3 start
{
	int	filefd;
	int	total_len;

	// set_elements(info, cmd_index);
	if (info->is_here_doc == true && cmd_index == 0)
	{
		// fprintf("%s\n", info->total_document);
		total_len = ft_strlen(info->total_document);
		safe_func(close(info->pipefd[0][0]), info);
		write(info->pipefd[0][1], info->total_document, total_len);
		close(info->pipefd[0][1]);
		exit(0);
	}
	filefd = get_filefd(info, cmd_index);
	if (filefd == -1)
	{
		perror(info->file);
		free_all_info(info, false);
		exit(1);
	}
	dup2_func(info, filefd, cmd_index);
	close_func(info, filefd, cmd_index);
	// fprintf(stderr, "100: %s\n", info->cmd_full_path[cmd_index]);
	execve(info->cmd_full_path[cmd_index], info->cmd[cmd_index], info->envp);
	// fprintf(stderr, "102: %s\n", info->cmd_full_path[cmd_index]);

	// ft_putendl_fd("pipex: illegal option", 2);
	exit(127);
}

int	start_process(t_info info)
{
	int	wstatus;
	int	cmd_index;

	cmd_index =0;//info.is_here_doc;  // index 整える
	while (cmd_index < info.process_cnt) // argc: 5
	{
		set_elements(&info, cmd_index);  // 子プロセスでやるべき？
		if (cmd_index + info.first_cmd_index != info.argc - 2 && (pipe(info.pipefd[cmd_index]) < 0))
			exit(free_all_info(&info, true));
		info.pid[cmd_index] = fork();
		if (info.pid[cmd_index] == -1)
			exit(free_all_info(&info, true));
		else if (info.pid[cmd_index] == 0)
			child_exe(&info, cmd_index); // 0 start
		else
		{
			if (cmd_index != 0) // cmd_index = 3 4
			{
				close(info.pipefd[cmd_index - 1][0]);
				close(info.pipefd[cmd_index - 1][1]);
			}
		}
		cmd_index++;
	}
	info.cmd_full_path[cmd_index] = NULL;
	cmd_index = 0;
	while (cmd_index < info.process_cnt)
	{
		safe_func(waitpid(info.pid[cmd_index], &wstatus, WUNTRACED), &info);
		// printf("125: %d %d\n", res, wstatus);
		// printf("127: %d %d %d\n", cmd_index, WIFEXITED(wstatus), WEXITSTATUS(wstatus));
		cmd_index++;
	}
	// printf("\n");
	// exit(info.error_status);
	// exit(wstatus);  // 終了ステータス
	return (WEXITSTATUS(wstatus));
}



