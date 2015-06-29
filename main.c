#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "bh_thread_pool.h"

void test_print(int data) {
    int i;
    for (i=0; i<1000000; i++) {
        data += 1;
    }
}

int
get_random(int min, int max) {
    return (rand()%(max-min))+min;
}

int
main() {
    int count = 0;
    bh_thread_pool *pool = bh_thread_pool_create(4, 512);
    sleep(1);
    while (count < 10000) {
        bh_thread_pool_add_task(pool, test_print, get_random(1, 65535), count++);
    }

    bh_thread_pool_release(pool);
}
