#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

void child() {
  printf(" CHILD <%ld> My PID is <%ld> and my parent got PID <%ld>.\n",
         (long) getpid(), (long) getpid(), (long) getppid());
  printf(" CHILD <%ld> Goodbye!\n", (long) getpid());
  exit(EXIT_SUCCESS);
}

void parent(pid_t pid) {
  printf("PARENT <%ld> My PID is <%ld> and I spawned a child with PID <%ld>.\n",
         (long) getpid(), (long) getpid(), (long) pid);
  printf("PARENT <%ld> Goodbye!\n", (long) getpid());
  exit(EXIT_SUCCESS);
}

int main(void) {
  pid_t pid;

  switch (pid = fork()) {
    case -1:       // On error fork() returns -1.
      perror("fork failed");
      exit(EXIT_FAILURE);
    case 0:       // On success fork() returns 0 in the child.
      child();
    default:      // On success fork() returns the pid of the child to the parent.
      parent(pid);
  }
}


// output:
// 
// PARENT <12> My PID is <12> and I spawned a child with PID <13>.
// PARENT <12> Goodbye!
//  CHILD <13> I'm alive! My PID is <13> and my parent got PID <12>.
//  CHILD <13> Goodbye!