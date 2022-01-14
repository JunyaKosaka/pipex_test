#include "pipex.h"

static	int	get_path_index(t_info info)
{
	int	index;

	index = 0;
	while (info.envp[index])
	{
		if (!ft_strncmp(info.envp[index], "PATH=", PATH_PREFIX))
			return (index);
		index++;
	}
	return (-1);
}

void	convert_to_cmd_full_path(t_info *info, int cmd_index)
{
	char	**all_paths;
	int		env_index;
	int		path_index;

	if (!access(info->cmd[cmd_index][0], X_OK))
	{
		info->cmd_full_path[cmd_index] = ft_strdup(info->cmd[cmd_index][0]);
		return ;
	}
	env_index = get_path_index(*info);
	if (env_index == -1)
		exit(1);
	all_paths = ft_split(&(info->envp[env_index][PATH_PREFIX]), ':');
	if (!all_paths)
		exit(free_all_info(info, true));
	path_index = 0;
	while (all_paths[path_index])
	{
		char *temp;
		temp = ft_strjoin(all_paths[path_index], "/");
		info->cmd_full_path[cmd_index] = ft_strjoin(temp, info->cmd[cmd_index][0]);
		free(temp);
		if (!info->cmd_full_path[cmd_index])
		{
			free_2arr((void **)all_paths);
			exit(free_all_info(info, true));
		}
		if (!access(info->cmd_full_path[cmd_index], X_OK))
		{
			free_2arr((void **)all_paths);
			return ;
		}
		free(info->cmd_full_path[cmd_index]);
		info->cmd_full_path[cmd_index] = NULL;
		path_index++;
	}
	info->cmd_full_path[cmd_index] = ft_strdup("");
	free_2arr((void **)all_paths);
	write(STDERR, "pipex: command not found: ", 26);
	ft_putendl_fd(info->cmd[cmd_index][0], STDERR);
	//execveで127設定
}
