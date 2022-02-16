#include "minitalk.h"

//클라이언트 신호 처리 후 출력한 다음 서버의 출력상태를 클라이언트에게 보내는 함수
static void	print_str(int sig, siginfo_t *info, void *context)
{
	static int				recv_cnt = 0; //클라이언트에게 받은 신호 횟수(8개 받을 예정)
	static unsigned char	ascii = 0; //기본문자 00000000으로 설정

	ascii |= (sig == ONE); //or비트연산으로 받은 신호를 8bit 가장 오른쪽에 배치
	if (++recv_cnt < 8)
	{
		ascii <<= 1; //8개의 비트가 완성 될 때까지 비트를 한자리씩 왼쪽으로 민다. 
		return ;
	}
	recv_cnt = 0; //8개의 비트가 완성되면 신호횟수를 0으로 초기화하고 아래 동작 실행
	if (ascii != '\0') //완성된 문자가 NULL문자가 아니면
	{
		ft_putchar_fd(ascii, 1); //완성된 문자 출력
		kill(info->si_pid, ONE); //클라이언트에 ONE신호를 보내고
		ascii = 0;				//문자 정적변수 초기화
		return ;
	}
	ft_putstr_fd("\nCLIENT PID:	", 1);
	ft_putnbr_fd(info->si_pid, 1); //만약 NULL문자(종료)이면 클라이언트의 pid출력하고
	ft_putchar_fd('\n', 1);
	kill(info->si_pid, ZERO); //클라이언트에 ZERO신호를 보내서 마무리
	context = (void *)context; //(unuse param 처리)
}

int	main(void)
{
	struct sigaction	sig;

	ft_putstr_fd("SERVER PID:	", 1);
	ft_putnbr_fd(getpid(), 1); //현재 server의 pid출력
	ft_putchar_fd('\n', 1);
	sig.sa_sigaction = print_str; //신호를 받으면 사용 할 함수를 sigaction구조체에 대입
	sig.sa_flags = SA_SIGINFO; //옵션설정, sa_handler대신 sa_sigaction을 사용하도록 변경하는 옵션
	sigaction(ZERO, &sig, 0); //ZERO신호에 대한 신호처리
	sigaction(ONE, &sig, 0); //ONE신호에 대한 신호처리
	while (1)
		pause(); //client의 신호를 기다림
	return (0);
}
