
#include "types.h"
#include "user.h"

void sem_init(struct semaphore* sem, int initval)
{
sem->sema_value = 0;
sem->sema_waiters = 0;

mutex_init(&sem->sema_mutex);
cv_init(sem->condvar);

}

void sem_wait(struct semaphore* sem)
{

mutex_lock(&sem->sema_mutex);
while (sem->sema_value == 0){
  sem->sema_waiters++;
  cv_wait(&sem->sema_condvar, &sem->sema_mutex);
  sem->sema_waiters--;
}
sem->sema_value--;

mutex_unlock(&sem->sema_mutex);

}

void sem_post(struct semaphore* sem)
{

mutex_lock(&sem->sema_mutex)
sem->sema_value ++;
  if(sem->sema_waiters > 0 && sem->semavalue > 0)
  {
    cv_signal(&sem->sema_cv);
  }
mutex_unlock(&sem->sema_mutex);

}

