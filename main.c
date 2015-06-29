#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "bh_thread_pool.h"

void normal_task(int task_address, int sock_fd, int data) {
    int i;
    printf("%d===%d: %d\n", task_address, sock_fd, data);
}

void special_task(int task_address, int sock_fd, int data, int special) {
    int i;
    printf("%d===%d: %d\n", task_address, sock_fd, data);
}

int
get_random(int min, int max) {
    return (rand()%(max-min))+min;
}

int
main() {
    int count = 0;
    bh_thread_pool *pool = bh_thread_pool_create(4, 4);
    sleep(1);
    while (count < 30) {
        if (count%10 == 0) {
            bh_thread_pool_add_special_task(pool, special_task, special, get_random(1, 5), count++, 0);
        } else {
            bh_thread_pool_add_normal_task(pool, normal_task, normal, get_random(1, 5), count++);
        }
    }

    bh_thread_pool_release(pool);
}
