/* clone with bad stack argument */
#include "types.h"
#include "user.h"

#undef NULL
#define NULL ((void*)0)

#define PGSIZE (4096)

int ppid;

#define assert(x) if (x) {} else { \
   printf(1, "%s: %d ", __FILE__, __LINE__); \
   printf(1, "assert failed (%s)\n", # x); \
   printf(1, "TEST FAILED\n"); \
   kill(ppid); \
   exit(); \
}

void worker(void *arg_ptr);

int
main(int argc, char *argv[])
{
   ppid = getpid();
   void *ustack = malloc(PGSIZE*2);
   assert(ustack != NULL);
   if((uint)ustack % PGSIZE == 0)
     ustack += 4;

   assert(clone(worker, 0, ustack) == -1);

   ustack = sbrk(0);
   if((uint)ustack % PGSIZE)
     ustack = ustack + (PGSIZE - (uint)ustack % PGSIZE);
   sbrk( ((uint)ustack - (uint)sbrk(0)) + PGSIZE/2 );
   assert((uint)ustack % PGSIZE == 0);
   assert((uint)sbrk(0) - (uint)ustack == PGSIZE/2);

   assert(clone(worker, 0, ustack) == -1);

   printf(1, "TEST PASSED\n");
   exit();
}

void
worker(void *arg_ptr) {
   exit();
}
