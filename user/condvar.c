
#include "types.h"
#include "user.h"

void cv_init(struct condvar* cv)
{
/*
int error;
 
error = ___lwp_cond_wait(cv, mp, NULL, 0);
if (mp->mutex_type & (PTHREAD_PRIO_INHERIT|PTHREAD_PRIO_PROTECT))
(void) ___lwp_mutex_timedlock(mp, NULL, NULL);
else
(void) _lwp_mutex_lock(mp);
return (error); 
*/
}

void cv_wait(struct condvar* cv, struct mutex* mtx)
{
/* grabbed from solaris source code
int error;
 
error = ___lwp_cond_wait(cv, mp, NULL, 0);
if (mp->mutex_type & (PTHREAD_PRIO_INHERIT|PTHREAD_PRIO_PROTECT))
(void) ___lwp_mutex_timedlock(mp, NULL, NULL);
else
(void) _lwp_mutex_lock(mp);
return (error); 
*/
}

void cv_signal(struct condvar* cv)
{
	/* fill this in! */
}

void cv_broadcast(struct condvar* cv)
{
	/* fill this in! */
}
