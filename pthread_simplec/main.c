#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

typedef void   (* die_f  )(void * node);
typedef void * (* start_f)(void * arg );

//
// async_run - 开启一个自销毁的线程 运行 run
// run		: 运行的主体
// arg		: run的参数
// return	: >= 0 表示成功
//
int async_run_(die_f run, void * arg);
#define async_run(run, arg) async_run_((die_f)(run), arg)

static void _loop(int * ptr) {
	int num = *ptr;
	puts("_loop num begin");
	while (num > 0) {
		printf("_loop num = %07d.\n", num);
		*ptr = --num;
	}
	puts("_loop num e n d");
}

//
// pthread x86 lib use demo
//
int main(int argc, char * argv[]) {
	volatile int num = BUFSIZ;
	async_run(_loop, (void *)&num);
	while (num + num > BUFSIZ)
		;
	return EXIT_SUCCESS;
}

// 运行的主体
struct func {
	die_f run;
	void * arg;
};

// thread_run 中 pthread 执行的实体
static inline void * _run(struct func * func) {
	func->run(func->arg);
	free(func);
	return NULL;
}

int
async_run_(die_f run, void * arg) {
	pthread_t tid;
	pthread_attr_t attr;
	struct func * func = malloc(sizeof(struct func));
	if (NULL == func) {
		fprintf(stderr, "malloc sizeof(struct func) is error\n");
		return -1;
	}

	func->run = run;
	func->arg = arg;

	// 构建pthread 线程奔跑起来
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);

	if (pthread_create(&tid, &attr, (start_f)_run, func) < 0) {
		free(func);
		pthread_attr_destroy(&attr);
		fprintf(stderr, "pthread_create error run, arg = %p | %p.\n", run, arg);
		return -1;
	}

	pthread_attr_destroy(&attr);
	return 0;
}