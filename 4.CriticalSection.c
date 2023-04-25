#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#define MAX 1e9
int turn, ans = 0, flag[2];
void lock_init()
{
    flag[0] = flag[1] = 0;
    turn = 0;
}
void lock(int self)
{
    flag[self] = 1;
    turn = 1 - self;
    while (flag[1 - self] == 1 && turn == 1 - self)
        ;
}
void unlock(int self) { flag[self] = 0; }
void *func(void *s)
{
    int i = 0;
    int *limitptr = (int *)s;
    int self = *limitptr;
    printf("Thread %d in queue for critical section\n", self);
    lock(self);
    printf("Thread %d entered critical section\n", self);
    for (i = 0; i < MAX; i++)
        ans++;
    printf("Thread %d completed executing\n", self);
    printf("Thread %d is exiting critical section\n", self);
    unlock(self);
}
int main()
{
    pthread_t p1, p2;
    int a = 0, b = 1;
    lock_init();
    pthread_create(&p1, NULL, func, &a);
    pthread_create(&p2, NULL, func, &b);
    pthread_join(p1, NULL);
    pthread_join(p2, NULL);
    printf("Exiting main()\n");
    return 0;
}