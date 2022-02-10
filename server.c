#include "minitalk.h"

static void	print_str(int sig, siginfo_t *info, void *context)
{
	static int				recv_cnt = 0;
	static unsigned char	ascii = 0;

	ascii |= (sig == ONE);
	if (++recv_cnt < 8)
	{
		ascii <<= 1;
		return ;
	}
	recv_cnt = 0;
	if (ascii != '\0')
	{
		ft_putchar_fd(ascii, 1);
		kill(info->si_pid, ONE);
		ascii = 0;
		return ;
	}
	ft_putstr_fd("\nCLIENT PID:	", 1);
	ft_putnbr_fd(info->si_pid, 1);
	ft_putchar_fd('\n', 1);
	kill(info->si_pid, ZERO);
	context = (void *)context;
}

int	main(void)
{
	struct sigaction	sig;

	ft_putstr_fd("SERVER PID:	", 1);
	ft_putnbr_fd(getpid(), 1);
	ft_putchar_fd('\n', 1);
	sig.sa_sigaction = print_str;
	sig.sa_flags = SA_SIGINFO;
	sigaction(ZERO, &sig, 0);
	sigaction(ONE, &sig, 0);
	while (1)
		pause();
	return (0);
}
