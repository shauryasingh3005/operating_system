#include "types.h"
#include "stat.h"
#include "user.h"

// A heavy loop to burn CPU cycles and simulate work
void compute(int ticks) {
    int i, j;
    for(i = 0; i < ticks; i++) {
        for(j = 0; j < 5000000; j++) {
            asm("nop"); 
        }
        // Print progress every 100 iterations so you can visually see preemption
        if (i > 0 && i % 100 == 0) {
            printf(1, "[PID %d] running (remaining loops: %d)\n", getpid(), ticks - i);
        }
    }
}

int main(void) {
    // 1. Give the parent ultimate priority so it doesn't get starved!
    setburst(getpid(), 10);
    printf(1, "Starting SRTF Test...\n");

    // 2. LONG JOB
    int pid1 = fork();
    if(pid1 == 0) {
        compute(500); 
        printf(1, "\n--- Long job (PID %d) finished ---\n", getpid());
        exit();
    }
    // PARENT sets the child's burst time immediately so it doesn't get starved!
    setburst(pid1, 500);
    printf(1, "Spawned Long Job (PID %d, Burst 500)\n", pid1);

    sleep(10); // Wait for a moment to let Long Job run
    setburst(getpid(), 10); // Refresh parent's high priority

    // 3. MEDIUM JOB
    int pid2 = fork();
    if(pid2 == 0) {
        compute(300); 
        printf(1, "\n--- Medium job (PID %d) finished ---\n", getpid());
        exit();
    }
    setburst(pid2, 300); 
    printf(1, "Spawned Medium Job (PID %d, Burst 300)\n", pid2);

    sleep(10);
    setburst(getpid(), 10); 

    // 4. SHORT JOB
    int pid3 = fork();
    if(pid3 == 0) {
        compute(100); 
        printf(1, "\n--- Short job (PID %d) finished ---\n", getpid());
        exit();
    }
    setburst(pid3, 100);
    printf(1, "Spawned Short Job (PID %d, Burst 100)\n", pid3);

    // Parent waits for all children to die
    wait(); 
    wait(); 
    wait();
    
    printf(1, "Test Complete.\n");
    exit();
}
