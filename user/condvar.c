
#include "types.h"
#include "user.h"

void cv_init(struct condvar* cv)
{
  cv->condvar_description = desc;
  cv->condvar_waiters = 0;
}

void cv_wait(struct condvar* cv, struct mutex* mtx)
{
/*
	WITNESS_SAVE_DECL(lock_witness);
	struct lock_class *class;
	struct thread *td;
	uintptr_t lock_state;

	td = curthread;
	lock_state = 0;
	class = LOCK_CLASS(lock);

	sleepq_lock(cvp);

	cvp->cv_waiters++;
	if (lock == &Giant.lock_object)
		mtx_assert(&Giant, MA_OWNED);
	DROP_GIANT();

	sleepq_add(cvp, lock, cvp->cv_description, SLEEPQ_CONDVAR, 0);
	if (lock != &Giant.lock_object) {
		if (class->lc_flags & LC_SLEEPABLE)
			sleepq_release(cvp);
		WITNESS_SAVE(lock, lock_witness);
		lock_state = class->lc_unlock(lock);
		if (class->lc_flags & LC_SLEEPABLE)
			sleepq_lock(cvp);
	}
	sleepq_wait(cvp, 0);

	PICKUP_GIANT();
	if (lock != &Giant.lock_object) {
		class->lc_lock(lock, lock_state);
		WITNESS_RESTORE(lock, lock_witness);
	}
}
*/
}



 
void cv_signal(struct condvar* cv)
{

  int wakeup_swapper;
  wakeup_swapper = 0;
  park(cv);
  if(cv->condvar_waiters > 0) {
    cv->condvar_waiters--;
  //  wakeup_swapper = unpark(
/*
	wakeup_swapper = sleepq_signal(cvp, SLEEPQ_CONDVAR, 0, 0);
  }
  sleepq_release(cvp);
  if (wakeup_swapper)
  	kick_proc0();
}
*/
  }
/*
sleepq_release(void *wchan)
{
	struct sleepqueue_chain *sc;

	sc = SC_LOOKUP(wchan);
	mtx_unlock_spin(&sc->sc_lock);
*/



}










void cv_broadcast(struct condvar* cv)
{
  int wakeup_swapper;
  wakeup_swapper = 0;
  sleepq_lock(cvp);
  if (cv->condvar_waiters > 0) {
  	cv->condvar_waiters = 0;
  	wakeup_swapper = wakeup()	
//wakeup_swapper = sleepq_broadcast(cvp, SLEEPQ_CONDVAR, pri, 0);
  }
  sleepq_release(cvp);
  if (wakeup_swapper)
  	kick_proc0();
}











}
