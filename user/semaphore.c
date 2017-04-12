
#include "types.h"
#include "user.h"

void sem_init(struct semaphore* sem, int initval)
{
/* grabbed from linux kern
void
sema_init(struct sema *sema, int value, const char *description)
{

	KASSERT((value >= 0), ("%s(): negative value\n", __func__));

	bzero(sema, sizeof(*sema));
	mtx_init(&sema->sema_mtx, description, "sema backing lock",
	    MTX_DEF | MTX_NOWITNESS | MTX_QUIET);
	cv_init(&sema->sema_cv, description);
	sema->sema_value = value;

	CTR4(KTR_LOCK, "%s(%p, %d, \"%s\")", __func__, sema, value, description);
}

*/


/* grabbed from solaris source code
int
sema_init(sema_t *sp, unsigned int count, int type, void *arg)
{
if (_semvaluemax == 0)
_semvaluemax = (uint32_t)_sysconf(_SC_SEM_VALUE_MAX);
if ((type != USYNC_THREAD && type != USYNC_PROCESS) ||
(count > _semvaluemax))
return (EINVAL);
(void) memset(sp, 0, sizeof (*sp));
sp->count = count;
sp->type = (uint16_t)type;
sp->magic = SEMA_MAGIC;
 

This should be at the beginning of the function,
but for the sake of old broken applications that
do not have proper alignment for their semaphores
(and don't check the return code from sema_init),
we put it here, after initializing the semaphore regardless.

if (((uintptr_t)sp & (_LONG_LONG_ALIGNMENT - 1)) &&
curthread->ul_misaligned == 0)
return (EINVAL);

return (0);
}
*/
}

void sem_wait(struct semaphore* sem)
{

/*
grabbed from linux kern
void
_sema_wait(struct sema *sema, const char *file, int line)
{

	mtx_lock(&sema->sema_mtx);
	while (sema->sema_value == 0) {
		sema->sema_waiters++;
		cv_wait(&sema->sema_cv, &sema->sema_mtx);
		sema->sema_waiters--;
	}
	sema->sema_value--;

	CTR6(KTR_LOCK, "%s(%p) \"%s\" v = %d at %s:%d", __func__, sema,
	    cv_wmesg(&sema->sema_cv), sema->sema_value, file, line);

	mtx_unlock(&sema->sema_mtx);
}


*/
/* grabbed from solaris source code 
#pragma weak _sema_wait = sema_wait
int
sema_wait(sema_t *sp)
{
ASSERT(!curthread->ul_critical || curthread->ul_bindflags);
return (sema_wait_impl(sp, NULL));
}
 
int
sema_reltimedwait(sema_t *sp, const timespec_t *reltime)
{
timespec_t tslocal = *reltime;
 
ASSERT(!curthread->ul_critical || curthread->ul_bindflags);
return (sema_wait_impl(sp, &tslocal));
}
 
int
sema_timedwait(sema_t *sp, const timespec_t *abstime)
{
timespec_t tslocal;
 
ASSERT(!curthread->ul_critical || curthread->ul_bindflags);
abstime_to_reltime(CLOCK_REALTIME, abstime, &tslocal);
return (sema_wait_impl(sp, &tslocal));
}

*/

}

void sem_post(struct semaphore* sem)
{

/* grabbed from linux kern
void
_sema_post(struct sema *sema, const char *file, int line)
{

	mtx_lock(&sema->sema_mtx);
	sema->sema_value++;
	if (sema->sema_waiters && sema->sema_value > 0)
		cv_signal(&sema->sema_cv);

	CTR6(KTR_LOCK, "%s(%p) \"%s\" v = %d at %s:%d", __func__, sema,
	    cv_wmesg(&sema->sema_cv), sema->sema_value, file, line);

	mtx_unlock(&sema->sema_mtx);
}

*/


/* grabbed from solaris source code
#pragma weak _sema_post = sema_post
int
sema_post(sema_t *sp)
{
lwp_sema_t *lsp = (lwp_sema_t *)sp;
ulwp_t *self = curthread;
uberdata_t *udp = self->ul_uberdata;
tdb_sema_stats_t *ssp = SEMA_STATS(sp, udp);
uint_t count;
int error = 0;
 
if (ssp)
tdb_incr(ssp->sema_post);
if (_semvaluemax == 0)
_semvaluemax = (uint32_t)_sysconf(_SC_SEM_VALUE_MAX);
 
if (lsp->type == USYNC_PROCESS) {     kernel-level 
error = _lwp_sema_post(lsp);
} else if (!udp->uberflags.uf_mt) {   single threaded 
sigoff(self);
if (lsp->count >= _semvaluemax)
error = EOVERFLOW;
else
lsp->count++;
sigon(self);
} else {                
//multithreaded 
queue_head_t *qp;
ulwp_t *ulwp;
lwpid_t lwpid = 0;
 
qp = queue_lock(lsp, CV);
if (lsp->count >= _semvaluemax)
error = EOVERFLOW;
else if (lsp->count++ == 0 && lsp->sema_waiters) {
int more;
if ((ulwp = dequeue(qp, &more)) != NULL) {
no_preempt(self);
lwpid = ulwp->ul_lwpid;
}
lsp->sema_waiters = more;
}
queue_unlock(qp);
if (lwpid) {
(void) __lwp_unpark(lwpid);
preempt(self);
}
}
 
if (error == 0) {
if (ssp) {
we just incremented the count 
count = lsp->count;
if (ssp->sema_max_count < count)
ssp->sema_max_count = count;

}
}

 
return (error);
}
*/
}

