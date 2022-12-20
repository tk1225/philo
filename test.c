#include <unistd.h>
#include <stdio.h>
#include <sys/time.h>

// int main (void){

// 	struct timeval now;
// 	int		ms;
// 	int		ms_wake;
// 	int		i;

// 	i = 0;

// 	while (i < 100)
// 	{
// 		gettimeofday(&now, NULL);
// 		ms = (now.tv_sec) * 1000 + (now.tv_usec) / 1000;
// 		// printf("%d_in_ms\n",ms);
// 		usleep(100000);

// 		gettimeofday(&now, NULL);
// 		ms_wake = (now.tv_sec) * 1000 + (now.tv_usec) / 1000;
// 		printf("%d_in_ms\n\n",ms_wake - ms);

// 		i ++;
// 	}
// 	return (0);
// }

size_t	get_mili_sec(void)
{
	struct timeval	now;
	size_t		ms;

	gettimeofday(&now, NULL);
	ms = (now.tv_sec) * 1000 + (now.tv_usec) / 1000;

	return (ms);
}

int main (void){

	struct timeval now;
	size_t		ms;
	size_t		ms_wake;
	int		i;

	i = 0;

	while (i < 100)
	{
		gettimeofday(&now, NULL);
		ms = (now.tv_sec) * 1000 + (now.tv_usec) / 1000;
		// printf("%d_in_ms\n",ms);

		printf("%zu_in_ms\n",ms);

		while((get_mili_sec() < ms + 100))
		{
			usleep(100);
		}

		gettimeofday(&now, NULL);
		ms_wake = (now.tv_sec) * 1000 + (now.tv_usec) / 1000;
		printf("%zu_in_ms\n\n",ms_wake - ms);

		i ++;
	}
	return (0);
}