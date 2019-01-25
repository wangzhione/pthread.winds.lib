#include "thread.h"

struct rwarg {
    pthread_rwlock_t lock;  // 读写锁

    unsigned id;            // 标识

    // conf 配置
    struct {
        char * description; // 描述
    };
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
    struct rwarg arg = { 
        .lock = PTHREAD_RWLOCK_INITIALIZER,
        .description = "爱我中华",
    };

    // 写程序跑起来
    pthread_async(reads, &arg);

    // 读线程跑起来
    for (int i = 0; i < 10; ++i)
        pthread_async(reads, &arg);

    // 写程序跑起来
    pthread_async(reads, &arg);

    // 简单等待一下
    puts("sleep input enter:");
    return getchar();
}

// write - 写线程, 随机写字符
void 
write(struct rwarg * arg) {
    pthread_rwlock_wrlock(&arg->lock);
    ++arg->id;
    arg->description = arg->id%2 ? "为人民服务" : "才刚刚开始";
    printf("write id[%u][%s]\n", arg->id, arg->description);
    pthread_rwlock_unlock(&arg->lock);
}

// reads - 读线程
void 
reads(struct rwarg * arg) {
    pthread_rwlock_rdlock(&arg->lock);
    ++arg->id;
    printf("reads id[%u][%s]\n", arg->id, arg->description);
    pthread_rwlock_unlock(&arg->lock);
}
