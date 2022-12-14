#include "philo.h"

// 新しいスレッドで実行されるタスク
int a = 0;
pthread_mutex_t mutex;

void *func_thread(void *p) {
  printf("start %d\n", *(int*)p);

  int i=0;
  for(i=0; i < 10000; i++){
    pthread_mutex_lock(&mutex);
	int next = a + 1;
	int now = a;
	a = next;
    pthread_mutex_unlock(&mutex);
	if (now+1 != next) {
	  printf("other theard change %d %d\n", a+1, next);
	}
  }

  return 0;
}

int main(void)
{
  
  pthread_mutex_init(&mutex, NULL);
  int b = 42;

  pthread_t pthread;
  pthread_create(&pthread, NULL, &func_thread, &b);
  //errorは０以外の戻り値

  int i=0;
  for(i=0; i < 10000; i++)
  {
    pthread_mutex_lock(&mutex);
	int next = a + 1;
	int now = a;
	a = next;
    pthread_mutex_unlock(&mutex);
	if (now+1 != next) {
	  printf("other theard change %d %d\n", a+1, next);
	}
  }

  pthread_join(pthread, NULL); // pthreadで作られたスレッドが終わるまで待つ
  //errorは０以外の戻り値

  printf("a=%d\n", a);

  return 0;
}