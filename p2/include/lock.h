#ifndef LOCK_H
#define LOCK_H
#include <thread.h>

typedef struct {
	enum {
	      UNLOCKED,
	      LOCKED,
	} status;
	// TODO: define a queue for the lock.
	queue_t* q;
} lock_t;

void lock_init(lock_t *);
void lock_acquire(lock_t *);
void lock_release(lock_t *);
void block(lock_t *);
void unblock(lock_t *);

#endif                          /* LOCK_H */
