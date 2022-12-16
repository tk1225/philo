#include "philo.h"

void print_timestamp(struct timeval start_time, struct timeval tv, int philo_id, int status)
{
	char *message;
	int		ms;

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
	ms = (tv.tv_sec - start_time.tv_sec) * 1000000 + (tv.tv_usec - start_time.tv_usec) / 10 * 10;
	printf("%d_in_ms %d %s\n", ms, philo_id, message);
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