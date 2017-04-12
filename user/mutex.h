
#ifndef MUTEX_H
#define MUTEX_H

struct mutex {
	atomic_long_t	owner;
	spinlock_t	wait_lock;
};

muvoid mutex_init(struct mutex* mtx);
void mutex_lock(struct mutex* mtx);
void mutex_unlock(struct mutex* mtx);


#endif

/*
grabbed from linux source code
struct mutex {
 52         atomic_long_t           owner;
 53         spinlock_t              wait_lock;
*/

/* grabbed from OSTEP
1 typedef struct __lock_t {
2 int flag;
3 int guard;
4 queue_t *q;
5 } lock_t;
*/


