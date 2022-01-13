#include "pipex.h"

static void	get_here_doc(t_info *info)
{
	int		len;
	char	*temp;

	info->total_document = ft_strdup("");
	if (!info->total_document)
		exit(error_handler());
	len = ft_strlen(info->limiter);
	info->limiter[len] = '\n';
	len++;
	temp = get_next_line(0);
	while (ft_strncmp(temp, info->limiter, len))
	{
		info->total_document = ft_strjoin(info->total_document, temp, 1);
		if (!info->total_document)
		{
			free(temp); // ダブルfree注意
			free(info->total_document);
		}
		free(temp);
		temp = get_next_line(0);  // aaa
	}
	free(temp);
}

static void	init_info(t_info *info)
{
	int	process_cnt;

	process_cnt = info->argc - 3 - info->is_here_doc;
	info->pid = (pid_t *)malloc(sizeof(pid_t) * process_cnt);
	if (!info->pid)
		exit(free_all_info(info, true));
	printf("37: %lu\n", sizeof(int *) * (process_cnt - 1));
	info->pipefd = (int **)malloc(sizeof(int *) * (process_cnt + 1));
	if (!info->pipefd)
		exit(free_all_info(info, true));
	info->pipefd[process_cnt] = NULL;
	info->cmd_full_path = (char **)malloc(sizeof(char *) * (process_cnt + 1));
	if (!info->cmd_full_path)
		exit(free_all_info(info, true));
	info->cmd_full_path[process_cnt] = NULL;
	info->cmd = (char ***)malloc(sizeof(char *) * (process_cnt + 1));
	if (!info->cmd)
		exit(free_all_info(info, true));
	info->cmd[process_cnt] = NULL;
}

int	main(int argc, char **argv, char **envp)
{
	t_info		info;
	int			i;

	printf("\n");
	info.argv = argv;
	info.argc = argc;
	info.envp = envp;
	info.error_status = 0;
	info.is_here_doc = false;
	info.total_document = NULL;
	info.cmd_full_path = NULL;
	if (!ft_strncmp(argv[1], "here_doc", 9))
	{
		if (argc < 6)
			exit(error_handler());
		info.is_here_doc = true;
		info.limiter = argv[2];
		get_here_doc(&info);
	}
	info.process_cnt = argc - 3 - info.is_here_doc;
	init_info(&info);
	i = 0;
	while (i < info.process_cnt) // 1つ多くとっている
	{
		info.pipefd[i] = (int *)malloc(sizeof(int) * 2);
		i++;
	}
	info.error_status = start_process(info);
	// return (info.error_status);
	// printf("last%d\n", errno);
	// exit(0);
	printf("return : %d\n", info.error_status);
	free_all_info(&info, false);
	system("leaks -q pipex");
	exit(info.error_status);
}
