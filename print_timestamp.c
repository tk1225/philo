#include "philo.h"

void print_timestamp(struct timeval start_time, int philo_id, int status)
{
	char *message;
	// size_t		ms;
	// struct timeval now;

	// gettimeofday(&now, NULL);
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
	else if (status == 55)
		message = "scanning**********";
	// ms = (now.tv_sec - start_time.tv_sec) * 1000 + (now.tv_usec - start_time.tv_usec) / 1000;
	// ms =  (start_time.tv_sec) * 1000 + (start_time.tv_usec) / 1000;
	// ms = (now.tv_sec) * 1000 + (now.tv_usec) / 1000;

	// (void)start_time;
	// (void)now;
	printf("%d_in_ms %d %s\n", get_now_time(start_time), philo_id, message);
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