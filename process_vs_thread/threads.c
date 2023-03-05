#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

int x = 2; // global x, accessible by all threads

void* routine() {
    printf("routine, Process id %d\n", getpid())
    x += 5; // global x
    sleep(2);
    printf("Value of x: %d\n", x); // 7
}

void* routine2() {
    printf("routine2, Process id %d\n", getpid())
    sleep(2);
    printf("Value of x: %d\n", x); // global x, 7
}

int main(int argc, char* argv[]) {
    pthread_t t1, t2;
    if (pthread_create(&t1, NULL, &routine, NULL)) {
        return 1;
    }
    if (pthread_create(&t2, NULL, &routine2, NULL)) {
        return 2;
    }
    if (pthread_join(t1, NULL)) {
        return 3;
    }
    if (pthread_join(t2, NULL)) {
        return 3;
    }
    return 0;
}