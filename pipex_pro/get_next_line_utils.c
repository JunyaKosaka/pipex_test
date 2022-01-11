#include "pipex.h"

void	*free_one(char **s)
{
	if (s)
	{
		free(*s);
		*s = NULL;
	}
	return (NULL);
}

void	*free_all(char **s1, char **s2)
{
	free_one(s1);
	free_one(s2);
	return (NULL);
}
