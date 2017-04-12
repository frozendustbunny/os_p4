
#include "types.h"
#include "user.h"

void mutex_init(struct mutex* mtx)
{
	/* fill this in! */

/* from solaris
Use pthread_mutex_init(3THR) to initialize the mutex pointed at by mp to its default value (mattr is NULL), or to specify mutex attributes that have already been set with pthread_mutexattr_init(). (For Solaris threads, see mutex_init(3THR).)

Prototype:
int	pthread_mutex_init(pthread_mutex_t *mp,
    const pthread_mutexattr_t *mattr);
#include <pthread.h>

pthread_mutex_t mp = PTHREAD_MUTEX_INITIALIZER;
pthread_mutexattr_t mattr;
int ret;

/* initialize a mutex to its default value 
ret = pthread_mutex_init(&mp, NULL);

/* initialize a mutex 
ret = pthread_mutex_init(&mp, &mattr); 
When the mutex is initialized, it is in an unlocked state. The mutex can be in memory shared between processes or in memory private to a process.
*/
}

void mutex_lock(struct mutex* mtx)
{
	/* fill this in! */

/*
pthread_mutex_lock(3THR)
Prototype:
int	pthread_mutex_lock(pthread_mutex_t *mutex); 
#include <pthread.h>

pthread_mutex_t mutex;
int ret;

ret = pthread_ mutex_lock(&mp); /* acquire the mutex

Use pthread_mutex_lock(3THR) to lock the mutex pointed to by mutex. When pthread_mutex_lock() returns, the mutex is locked and the calling thread is the owner. If the mutex is already locked and owned by another thread, the calling thread blocks until the mutex becomes available. (For Solaris threads, see mutex_lock(3THR).)

If the mutex type is PTHREAD_MUTEX_NORMAL, deadlock detection is not provided. Attempting to relock the mutex causes deadlock. If a thread attempts to unlock a mutex that it has not locked or a mutex that is unlocked, undefined behavior results.

If the mutex type is PTHREAD_MUTEX_ERRORCHECK, then error checking is provided. If a thread attempts to relock a mutex that it has already locked, an error will be returned. If a thread attempts to unlock a mutex that it has not locked or a mutex that is unlocked, an error will be returned.

If the mutex type is PTHREAD_MUTEX_RECURSIVE, then the mutex maintains the concept of a lock count. When a thread successfully acquires a mutex for the first time, the lock count is set to one. Every time a thread relocks this mutex, the lock count is incremented by one. Each time the thread unlocks the mutex, the lock count is decremented by one. When the lock count reaches zero, the mutex becomes available for other threads to acquire. If a thread attempts to unlock a mutex that it has not locked or a mutex which is unlocked, an error will be returned.

If the mutex type is PTHREAD_MUTEX_DEFAULT, attempting to recursively lock the mutex results in undefined behavior. Attempting to unlock the mutex if it was not locked by the calling thread results in undefined behavior. Attempting to unlock the mutex if it is not locked results in undefined behavior.
*/
}

void mutex_unlock(struct mutex* mtx)
{
	/* fill this in! */
/*
Use pthread_mutex_unlock(3THR) to unlock the mutex pointed to by mutex. (For Solaris threads, see mutex_unlock(3THR).)

Prototype:
int	pthread_mutex_unlock(pthread_mutex_t *mutex); 
#include <pthread.h>

pthread_mutex_t mutex;
int ret;

ret = pthread_mutex_unlock(&mutex); /* release the mutex 
pthread_mutex_unlock() releases the mutex object referenced by mutex. The manner in which a mutex is released is dependent upon the mutex's type attribute. If there are threads blocked on the mutex object referenced by mutex when pthread_mutex_unlock() is called, resulting in the mutex becoming available, the scheduling policy is used to determine which thread shall acquire the mutex. (In the case of PTHREAD_MUTEX_RECURSIVE mutexes, the mutex becomes available when the count reaches zero and the calling thread no longer has any locks on this mutex).

Return Values
pthread_mutex_unlock() returns zero after completing successfully. Any other return value indicates that an error occurred. When any of the following conditions occurs, the function fails and returns the corresponding value.
*/
}
