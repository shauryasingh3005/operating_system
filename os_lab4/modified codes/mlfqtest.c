#include "types.h"
#include "stat.h"
#include "user.h"

int main(void) {
  printf(1, "Starting MLFQ Test...\n");

  int pid1 = fork();
  if (pid1 == 0) {
    // CPU-Bound process (will sink to Level 2)
    printf(1, "CPU-bound process started (PID: %d)\n", getpid());
    while(1) {
      // Infinite loop to hog CPU
    }
  }

  int pid2 = fork();
  if (pid2 == 0) {
    // I/O-Bound process (will stay at Level 0)
    printf(1, "I/O-bound process started (PID: %d)\n", getpid());
    for(int i = 0; i < 10; i++) {
      sleep(10); // Voluntarily yield the CPU frequently
      printf(1, "I/O process woke up!\n");
    }
    exit();
  }

  // To truly verify the internal levels, you would normally add a cprintf() 
  // inside the trap.c demotion logic to print when a PID drops a level.
  wait();
  wait();
  exit();
}
