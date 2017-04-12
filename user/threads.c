
#include "types.h"
#include "stat.h"
#include "user.h"
#include "param.h"
#define PGSIZE (4096)
int thread_create(void (*fn)(void*), void *arg)
{
  void * ustack;
  ustack = malloc(2*4096);
  return clone(fn, arg, ustack);
}

int thread_join()
{
//  void * ustack;
//  int status = join(&ustack);
//  free(ustack);
//  return status;

  void** pp=malloc(sizeof(*pp));
  int pid=join(pp);

  free(*pp);
  free(pp);
  return pid;
}
