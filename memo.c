#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

void	ft_putnbr_fd(int n, int fd)
{
	char	c;
	char	nbr;

	c = '-';
	if (n == -2147483648)
	{
		nbr = -1 * (n / 1000000000) + '0';
		write (fd, &c, 1);
		write (fd, &nbr, 1);
		n = 147483648;
	}
	if (n < 0)
	{
		write(fd, &c, 1); n *= -1;
	}
	if (n >= 10)
		ft_putnbr_fd(n / 10, fd);
	nbr = (n % 10) + '0';
	write (fd, &nbr, 1);
}

int main(void)
{
		pid_t pid;
		int wstatus;

		pid = fork();
//		printf("print:%d\n", pid);
		
		if (pid != 0)
			waitpid(pid, &wstatus, WUNTRACED);	
		//printf("success:%d\n", pid);
		ft_putnbr_fd(pid, 1);
		write(1, "/", 1);
		exit(0);
}
