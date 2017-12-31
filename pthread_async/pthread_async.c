#include <stdio.h>
#include <pthread.h>

typedef void   (* node_f )(void * node);
typedef void * (* start_f)(void * arg );

//
// pthread_async_ - 开启一个自销毁线程运行 frun
// frun     : 运行的主体
// arg      : 运行的参数
// return   : >= 0 表示成功
//
int pthread_async_(node_f frun, void * arg);
#define pthread_async(frun, arg) \
pthread_async_((node_f)(frun), (void *)(intptr_t)arg)

static void _loop(int * ptr) {
	int num = *ptr;
	puts("_loop num begin");
	while (num + num > BUFSIZ) {
		printf("_loop num = %07d.\n", num);
		*ptr = --num;
	}
	puts("_loop num e n d");
}

//
// pthread lib use demo
//
int main(int argc, char * argv[]) {
	volatile int num = BUFSIZ;
	
    pthread_async(_loop, &num);

	while (num + num > BUFSIZ)
		;

	return EXIT_SUCCESS;
}

inline int
pthread_async_(node_f frun, void * arg) {
    int ret;
	pthread_t tid;
	pthread_attr_t attr;

	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
    
    // 构建 pthread 线程奔跑起来 
	if ((ret = pthread_create(&tid, &attr, (start_f)frun, arg)) < 0)
		fprintf(stderr, "pthread_create err frun, arg = %p | %p.\n", frun, arg);

	pthread_attr_destroy(&attr);

	return ret;
}
