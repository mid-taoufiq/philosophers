#include "philosophers.h"


typedef struct {
    int x;
    float y;
} MyArgs;

void *my_thread_func(void *arg) {
    MyArgs *args = (MyArgs *)arg;
    printf("x = %d, y = %f\n", args->x, args->y);
    return NULL;
}

int main() {
    pthread_t thread;
    pthread_t thread2;
    MyArgs args = { 10, 3.14 };
    pthread_create(&thread, NULL, my_thread_func, &args);
    pthread_create(&thread2, NULL, my_thread_func, &args);
    pthread_join(thread, NULL);
    pthread_join(thread2, NULL);
    return 0;
}