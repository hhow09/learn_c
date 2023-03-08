// compile: gcc -pthread peterson_spinlock.c -o peterson_spinlock
// ref: https://www.geeksforgeeks.org/petersons-algorithm-for-mutual-exclusion-set-1/
# include <stdio.h>
# include <pthread.h>

int flag[2];
int turn;
const int MAX=1e5;
int ans = 0;

void lock_init()
{
    // Initialize lock by resetting the desire of
    // both the threads to acquire the locks.
    // And, giving turn to one of them.
    flag[0] = flag[1] = 0;
    turn = 0;
}

// Executed before entering critical section
void lock(int self)
{
    // saying want to acquire lock 
    flag[self] = 1;

    // give the chance to the other thread 
    turn = 1-self;

    // Wait until the other thread release
    while (flag[1-self]==1 && turn==1-self);
}

void unlock(int self)
{
    flag[self] = 0;
}


// A Sample function run by two threads created
// in main()
void* func(void *s)
{
    int i = 0;
    int self = (int *)s;
    printf("Thread Entered: %d\n", self);
 
    lock(self);
 
    // Critical section (Only one thread
    // can enter here at a time)
    for (i=0; i<MAX; i++)
        ans++;
 
    unlock(self);
}

int main()
{
    pthread_t p1, p2;
    lock_init();
    
    
    pthread_create(&p1, NULL, func, (void*)0);
    pthread_create(&p2, NULL, func, (void*)1);

    pthread_join(p1, NULL);
    pthread_join(p2, NULL);

    printf("Actual Count: %d | Expected Count: %d\n", ans, MAX*2);
    return 0;
}