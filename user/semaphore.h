
#ifndef SEMAPHORE_H
#define SEMAPHORE_H

struct semaphore {
	struct mutex sema_mutex;	// general protection lock
	struct condvar sema_condvar;	// Waiters
	int sema_waiters;	// Number of waiters
	int sema_value;		// Semaphore value

//	uint sem_count;		// semaphore count
//	uint sem_type;		// semaphore type
//	uint sem_magic;		// semaphore magic

};

void sem_init(struct semaphore* sem, int initval);
void sem_post(struct semaphore* sem);
void sem_wait(struct semaphore* sem);

#endif


