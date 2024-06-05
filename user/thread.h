struct lock_t {
    unsigned int locked;
};

int thread_create(void *(start_routine)(void*), void *arg); 
void lock_init(struct lock_t* lock); 
void lock_acquire(struct lock_t* lock); 
void lock_release(struct lock_t* lock); 