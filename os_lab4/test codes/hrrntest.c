#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

void 
cpu_work(int n)
{
volatile int i;
volatile int x=0;
for(i=0;i<n;i++){
x+=i%7;
}
}

int 
main(void)
{
int pid;
printf("HRRN test started\n");

pid=fork();
if(pid==0){
set_burst(getpid(),30);
printf("Long process PID %d created, burst=30\n",getpid());

cpu_work(30000000);
printf("Long process PID %d completed\n",getpid());

exit(0);
}

pid=fork();

if(pid==0){
set_burst(getpid(),5);
printf("Short process PID %d started, burst=5\n",getpid());

cpu_work(50000000);

printf("Short process PID %d completed\n",getpid());

exit(0);
}

pid=fork();
if(pid==0){
set_burst(getpid(),10);
printf("Short Process PID %d started,burst =10\n",getpid());
cpu_work(50000000);
printf("Short process PID %d ended\n",getpid());

exit(0);
}

wait(0);
wait(0);
wait(0);

printf("HRRN test completed\n");
exit(0);
}

