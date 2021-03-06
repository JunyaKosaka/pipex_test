#include "pipex.h"

void	free_2arr(void **arr)
{
	int	i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		arr[i] = NULL;
		i++;
	}
	free(arr[i]);
	free(arr);
}

static void	free_info(t_info *info)
{
	int	process_cnt;

	process_cnt = info->argc - 3 - info->is_here_doc;
	if (!info)
		return ;
	free_2arr((void **)info->pipefd);
	free_2arr((void **)info->cmd_full_path);
	int	i = 0;
	while (info->cmd[i])
	{
		free_2arr((void **)(info->cmd[i]));
		i++;
	}
	free(info->cmd[i]);
	free(info->cmd);
	if (info->total_document)
		free(info->total_document);
	if (info->pid)
		free(info->pid);
}

int	free_all_info(t_info *info, bool is_error)
{
	if (info)
		free_info(info);
	if (is_error)
		return (error_handler());
	return (0);
}
