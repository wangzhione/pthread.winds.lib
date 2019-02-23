# window pthread

    Window pthread static lib

[pthread.2015](https://github.com/GerHobbelt/pthread-win32)

    Modify pthread build config and pthread include,  It ADAPTS to the C.
    
## Hello World

    1. 打开 pthread-win32 项目

        git clone git@github.com:GerHobbelt/pthread-win32.git
        cd pthread-win32

        best new Visual Studio open pthread.2015.sln

    2. 中间状态

![sln](./img/sln.png)

    3. 开始编译

        导出 static lib 和 sched.h pthread.h semaphore.h include

![sln](./img/lib.png)

    4. 学习开始

        通过本项目提供的演示, 开启 window ptrhead static lib Hello world 之旅~

### welcome posix thread, haha

```C
#ifndef _THREAD_H
#define _THREAD_H

#include "struct.h"
#include <pthread.h>
#include <semaphore.h>

//
// pthread_end - 等待线程运行结束
// tid      : 线程 id
// return   : void
//
inline void pthread_end(pthread_t id) {
    pthread_join(id, NULL);
}

//
// pthread_run - 启动线程
// p        : 指向线程 id 的指针
// frun     : node_f or start_f 运行主体
// arg      : 运行参数
// return   : 0 is success, -1 is error
//
inline int pthread_run(pthread_t * p, void * frun, void * arg) {
    return pthread_create(p, NULL, frun, arg);
}

//
// pthread_async - 启动无需等待的线程
// frun     : node_f or start_f 运行的主体
// arg      : 运行参数
// return   : 0 is success, -1 is error
// 
inline static int pthread_async(void * frun, void * arg) {
    pthread_t id;
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
    int ret = pthread_create(&id, &attr, frun, arg);
    pthread_attr_destroy(&attr);
    return ret;
}

#endif//_THREAD_H
```
