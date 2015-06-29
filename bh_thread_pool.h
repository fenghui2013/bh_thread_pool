#ifndef _BH_THREAD_POOL_H_
#define _BH_THREAD_POOL_H_

typedef struct bh_thread_pool bh_thread_pool;

typedef void (*bh_normal_task)(int task_address, int sock_fd, int data);
typedef void (*bh_special_task)(int task_address, int sock_fd, int data, int special);

enum {
    normal = 1,
    special
};

bh_thread_pool * bh_thread_pool_create(int max_threads, int queue_size);
void             bh_thread_pool_add_normal_task(bh_thread_pool *thread_pool, bh_normal_task normal_task, int task_type, int sock_fd, int data);
void             bh_thread_pool_add_special_task(bh_thread_pool *thread_pool, bh_special_task special_task, int task_type, int sock_fd, int data, int special);
void             bh_thread_pool_release(bh_thread_pool *thread_pool);
#endif
