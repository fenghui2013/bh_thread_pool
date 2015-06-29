#ifndef _BH_THREAD_POOL_H_
#define _BH_THREAD_POOL_H_

typedef struct bh_thread_pool bh_thread_pool;

typedef void (*bh_task)(int data);

bh_thread_pool * bh_thread_pool_create(int max_threads, int queue_size);
void             bh_thread_pool_add_task(bh_thread_pool *thread_pool, bh_task task, int sock_fd, int data);
void             bh_thread_pool_release(bh_thread_pool *thread_pool);
#endif
