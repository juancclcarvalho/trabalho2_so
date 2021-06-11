#include <lock.h>
#include <threadu.h>

enum {
      SPIN = TRUE,
};

// TODO: inicializes a lock
void lock_init(lock_t * l)
{
	if (SPIN) {
		l->status = UNLOCKED;
	} else {
	}
}

// TODO:  acquires a  lock if  it is  available or  blocks the  thread
// otherwise
void lock_acquire(lock_t * l)
{
	if (SPIN) {
		while (LOCKED == l->status)
			thread_yield();
		l->status = LOCKED;
	} else {
	}
}

// TODO:  releases a  lock  and  unlocks one  thread  from the  lock's
// blocking list
void lock_release(lock_t * l)
{
	if (SPIN) {
		l->status = UNLOCKED;
	} else {
	}
}

// TODO: blocks the running thread
void block()
{
}

// TODO: unblocks  a thread that is waiting on a lock.
void unblock(lock_t *l)
{
}
