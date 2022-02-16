#include "minitalk.h"

//서버가 보낸 byte를 기록하고, 종료신호를 받으면 받은 byte를 출력하는 함수 
static void	recv_counter(int sig)
{
	static int	recv = 0; //정적변수로 ONE이 수신된 만큼 저장

	if (sig == ONE)
		recv += 1;
	else //ZERO가 수신되면 모아둔 recv를 출력하고 종료
	{
		ft_putnbr_fd(recv, 1);
		ft_putstr_fd("byte\n", 1);
		exit(0);
	}
}

//지정된 pid에 문자열을 0과 1의 bit단위로 보내는 함수
static void	send_str(int pid, char *str)
{
	int		i;

	while (1)
	{ //문자열을 8비트씩 끊어서 전송할 예정 (unsigned char = 8bit)
		i = 8; //8개의 bit를 보낼 예정
		while (i--) //반복문을 돌면서 하나씩 보낸다.
		{
			if (*str & (1 << i)) //현재 문자의 8개중 i번째 bit전송
				kill(pid, ONE); //만약 i번째비트가 1이라면 ONE신호 보냄
			else
				kill(pid, ZERO); //만약 현재 비트가 0이라면 ZERO신호 보냄
			usleep(100); //100마이크로초 기다림 (너무 빨리보내면 무시당함)
		}				//(usleep을 느리게 보내면 늦게 출력됨)
		if (*str++ == '\0') //문자열주소를  1칸(8비트) 이동, 이동한 주소가 NULL문자면 종료
			return ;
	}
}

int	main(int argc, char **argv)
{
	if (argc != 3 || !ft_strlen(argv[2])) //인자가 2개가 아니거나 빈문자열이면 종료
		exit(0);
	signal(ZERO, recv_counter); //ZERO신호에 대한 신호처리
	signal(ONE, recv_counter); //ONE신호에 대한 신호처리
	ft_putstr_fd("PID :	", 1);
	ft_putnbr_fd(getpid(), 1); //현재 client의 pid출력 
	ft_putstr_fd("\nsend:	", 1);
	ft_putnbr_fd(ft_strlen(argv[2]), 1); //보낼 문자열 byte 출력
	ft_putstr_fd("byte\n", 1);
	ft_putstr_fd("recv:	", 1);
	send_str(ft_atoi(argv[1]), argv[2]); //인자로 받은 서버pid에 인자로 받았던 문자열 전송
	while (1)
		pause(); //서버의 신호를 기다림
	return (0);
}
