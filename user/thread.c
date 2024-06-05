#include "kernel/types.h" 
#include "user/thread.h"
#include "user/user.h"
#define PGSIZE 4096

int thread_create(void *(start_routine)(void*), void *arg) {
    void* stack = (void*) malloc(PGSIZE);
    int pid = clone(stack);
    if (pid != -1) {
        // call start routine
        (*start_routine)(arg);
        exit(0);
    } else {
        return -1;
    }
    return 0;
}

void lock_init(struct lock_t* lock) {
    lock->locked = 0;
}

void lock_acquire(struct lock_t* lock) {
    while(__sync_lock_test_and_set(&lock->locked, 1) != 0);
    __sync_synchronize();
}

void lock_release(struct lock_t* lock) {
    __sync_synchronize();
    __sync_lock_release(&lock->locked, 0);
}