#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

void busy(int n){
volatile int x=0;
for(int i=0;i<n*100000;i++)x++;
}

int main(void){
int pid;

//Process1: long burst
pid=fork();
if(pid==0){
set_burst(getpid(),40);
printf("Process 1 started(burst 40)\n");
busy(5);
busy(2000);
printf("Process 1 completed\n");
exit(0);}

busy(100);
//Process 2: short burst
pid=fork();
if(pid==0){
set_burst(getpid(),5);
printf("Process 2 started(burst 5)\n");
busy(5);
busy(300);
printf("Process 2 completed\n");
exit(0);
}

pid=fork();
if(pid==0){
set_burst(getpid(),15);
printf("Process 3 started(burst 15)\n");
busy(5);
busy(800);
printf("Process 3 completed\n");
exit(0);}

wait(0);
wait(0);
wait(0);

printf("SRTF test completed\n");
exit(0);
}
