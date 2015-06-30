#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "bh_thread_pool.h"

typedef struct bh_normal_task_arg bh_normal_task_arg;
struct bh_normal_task_arg {
    int sock_fd;
    int data;
};

void bh_normal(int sock_fd, int data) {
    //printf("%d: %d\n", sock_fd, data);
    int i;
    for (i=0; i<100000; i++) {
        data += 1;
    }
}

void bh_normal_task(void *task_arg) {
    bh_normal_task_arg *arg = (bh_normal_task_arg *)task_arg;
    bh_normal(arg->sock_fd, arg->data);
}

typedef struct bh_special_task_arg bh_special_task_arg;
struct bh_special_task_arg {
    int sock_fd;
    int data;
    int special;
};

void bh_special(int sock_fd, int data, int special) {
    //printf("%d: %d\n", sock_fd, data);
    int i;
    for (i=0; i<100000; i++) {
        data += 1;
    }
}


void bh_special_task(void *task_arg) {
    bh_special_task_arg *arg = (bh_special_task_arg *)task_arg;
    bh_special(arg->sock_fd, arg->data, arg->special);
}

void task_arg_handler(void *task_arg) {
    free(task_arg);
    task_arg = NULL;
}

int
get_random(int min, int max) {
    return (rand()%(max-min))+min;
}

int
main() {
    int count = 0;
    bh_normal_task_arg *normal_task_arg;
    bh_special_task_arg *special_task_arg;


    bh_thread_pool *pool = bh_thread_pool_create(4, 512);
    sleep(1);

    while (count < 100000) {
        if (count%10 == 0) {
            special_task_arg = (bh_special_task_arg *)malloc(sizeof(bh_special_task_arg));
            special_task_arg->sock_fd = get_random(1, 65535);
            special_task_arg->data = count++;
            special_task_arg->special = 0;
            bh_thread_pool_add_task(pool, bh_special_task, special_task_arg, special_task_arg->sock_fd, task_arg_handler);
        } else {
            normal_task_arg = (bh_normal_task_arg *)malloc(sizeof(bh_normal_task_arg));
            normal_task_arg->sock_fd = get_random(1, 65535);
            normal_task_arg->data = count++;
            bh_thread_pool_add_task(pool, bh_normal_task, normal_task_arg, normal_task_arg->sock_fd, task_arg_handler);
        }
    }

    bh_thread_pool_release(pool);
}
