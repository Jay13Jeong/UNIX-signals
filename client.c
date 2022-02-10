#include "minitalk.h"

static void	recv_counter(int sig)
{
	static int	recv = 0;

	if (sig == ONE)
		recv += 1;
	else
	{
		ft_putnbr_fd(recv, 1);
		ft_putstr_fd("byte\n", 1);
		exit(0);
	}
}

static void	send_str(int pid, char *str)
{
	int		i;

	while (1)
	{
		i = 8;
		while (i--)
		{
			if (*str & (1 << i))
				kill(pid, ONE);
			else
				kill(pid, ZERO);
			usleep(100);
		}
		if (*str++ == '\0')
			return ;
	}
}

int	main(int argc, char **argv)
{
	if (argc != 3 || !ft_strlen(argv[2]))
		return (1);
	signal(ZERO, recv_counter);
	signal(ONE, recv_counter);
	ft_putstr_fd("PID :	", 1);
	ft_putnbr_fd(getpid(), 1);
	ft_putstr_fd("\nsend:	", 1);
	ft_putnbr_fd(ft_strlen(argv[2]), 1);
	ft_putstr_fd("byte\n", 1);
	ft_putstr_fd("recv:	", 1);
	send_str(ft_atoi(argv[1]), argv[2]);
	while (1)
		pause();
	return (0);
}
