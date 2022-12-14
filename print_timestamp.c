#include "philo.h"

void print_timestamp(struct timeval tv, int philo_num, int status)
{
	char *message;

	message = "";
	if (status == TAKEN_FORK)
		message = "has taken a fork";
	else if (status == EATING)
		message = "is eating";
	else if (status == SLEEPING)
		message = "is sleeping";
	else if (status == THINKING)
		message = "is thinking";
	else if (status == DIED)
		message = "died";
	printf("%d_in_ms %d %s", tv.tv_usec, philo_num, message);
}

// int main(void)
// {
//   	struct timeval tv;

//   	gettimeofday(&tv, NULL);
// 	//   printf("%06d\n", tv.tv_usec);
// 	//   gettimeofday(&tv, NULL);
// 	//   printf("%06d\n", tv.tv_usec);
// 	print_timestamp(tv, 1, 0);
//   	return 0;
// }