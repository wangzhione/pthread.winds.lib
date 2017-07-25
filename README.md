### pthread.winds.lib.2.7.0.1
    Winds pthread static lib 2.7.0.1 by gt VC14
    Top code by simplec, The relative pthread.2015 2.7.0.0 upgrade
    
### build code by pthread.2015
[pthread.2015](https://github.com/GerHobbelt/pthread-win32)

    Modify pthread build config and pthread include,  It ADAPTS to the C.

### welcome posix thread , haha
```C
#include <pthread.h>

/*
 * PThread Functions
 */
extern int __cdecl pthread_create (pthread_t * tid,
                            const pthread_attr_t * attr,
                            void * (__cdecl * start) (void *),
                            void * arg);
```
