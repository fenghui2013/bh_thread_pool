all: main

main: bh_thread_pool.c main.c
	gcc -o $@ $^ -lpthread

clean:
	rm -rf main
