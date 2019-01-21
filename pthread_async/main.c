#include "thread.h"

#define TH_INT    (6)

struct rwarg {
    pthread_t id;
    pthread_rwlock_t lock;    // 读写锁
    char buf[BUFSIZ];         // 存储数据
    int idx;                  // buf 索引
};

// write - 写线程, 随机写字符
void write(struct rwarg * arg);
// reads - 读线程
void reads(struct rwarg * arg);

/*
 * 主函数测试线程读写逻辑
 * 少量写线程, 大量读线程测试
 */
int main(int argc, char * argv[]) {
    // 初始化 rwarg::rwlock
    struct rwarg arg = { .lock = PTHREAD_RWLOCK_INITIALIZER, };

    // 读写线程跑起来
    for (int i = 0; i < TH_INT; ++i) {
        pthread_async(reads, &arg);
        pthread_async(write, &arg);
        pthread_async(reads, &arg);
    }

    // 简单等待一下
    puts("sleep input enter:");
    return getchar();
}

// write - 写线程, 随机写字符
void 
write(struct rwarg * arg) {
    pthread_rwlock_wrlock(&arg->lock);
    arg->buf[arg->idx] = 'a' + arg->idx;
    ++arg->idx;
    printf("write idx[%-2d], buf[%-9s]\n", arg->idx, arg->buf);
    pthread_rwlock_unlock(&arg->lock);
}

// reads - 读线程
void 
reads(struct rwarg * arg) {
    pthread_rwlock_rdlock(&arg->lock);
    printf("reads idx[%2d], buf[%9s]\n", arg->idx, arg->buf);
    pthread_rwlock_unlock(&arg->lock);
}
