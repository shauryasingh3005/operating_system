#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int 
main(void)
{
int pid;
for(int i=0;i<3;i++){
pid=fork();
if(pid==0){
int mypid=getpid();
int priority=(i+1)*5;
set_priority(mypid,priority);
printf("Child PID %d running with priority %d\n",mypid,priority);
for(volatile int j=0;j<10000000;j++);
printf("child pid %d finished\n",mypid);
exit(0);
}
}
for(int i=0;i<3;i++)
wait(0);
printf("Priority test completed\n");
exit(0);
}


