#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

int main(int argc, char* argv[]) {
    int x = 2;
    int pid = fork();
    if (pid == -1) {
        return 1;
    }
    printf("Process id %d\n", getpid()); // different btwn parrent and child
    if (pid == 0) { // child process only
        x++; // 
    }
    // both parent and child
    sleep(2);
    printf("Value of x: %d\n", x); 
                                   // because parent and child have different variable

    if (pid != 0) { // parent: wait child process
        wait(NULL);
    }
    return 0;
}

// [output]
// Process id 56075
// Process id 56076
// Value of x: 2
// Value of x: 3
