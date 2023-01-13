#include "philo.h"

void print_timestamp(struct timeval start_time, int philo_id, int status, pthread_mutex_t 	*action_mutex)
{
	char *message;
	// (void)action_mutex;
	pthread_mutex_lock(action_mutex);
	message = "";
	if (status == TAKEN_FORK)
		message = "has taken a fork";
	else if (status == EATING)
	{
		message = "\x1b[31mis eating\x1b[39m";
	}
	else if (status == SLEEPING)
		message = "\x1b[34mis sleeping\x1b[39m";
	else if (status == THINKING)
		message = "is thinking";
	else if (status == DIED)
		message = "died";
	printf("%d_in_ms %d %s\n", get_now_time(start_time), philo_id, message);
	pthread_mutex_unlock(action_mutex);
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