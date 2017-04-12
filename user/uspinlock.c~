#include "types.h"
#include "user.h"
#include "x86.h"
//#include "uspinlock.h"
 

void spin_init(struct spinlock* lk)
{
	lk->locked = 0;
}

void spin_lock(struct spinlock *lk)
{
	while(xchg(&lk->locked, 1) == 1);
}

void spin_unlock(struct spinlock *lk)
{
	lk->locked = 0; 
//	xchg(&lk->locked,0);
}
