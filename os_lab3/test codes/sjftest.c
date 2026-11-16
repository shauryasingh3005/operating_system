#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

void
work(int n)
{
volatile int i;
for(i=0; i<n*10000000;i++)
;}
int 
main(void)
{
int pid;

printf("SJF test started\n");

pid=fork();
if(pid==0){
int me=getpid();
printf("P%d: burst=30\n",me);
work(30);

printf("P%d: finished\n",me);
exit(0);
}
set_burst(pid,30);

pid=fork();
if(pid==0){
int me=getpid();
printf("P%d: burst=20\n",me);
work(20);

printf("P%d: finished\n",me);
exit(0);
}
set_burst(pid,20);

pid=fork();
if(pid==0){
int me=getpid();
printf("%d: burst=10\n",me);
work(10);
printf("%d: finished\n",me);
exit(0);
}
set_burst(pid,10);
pid=fork();
if(pid==0){
int me=getpid();
printf("%d: burst=40\n",me);
work(40);
printf("%d: finished\n",me);
exit(0);
}
set_burst(pid,40);
wait(0);
wait(0);
wait(0);
wait(0);

printf("SJF test completed\n");
exit(0);
}
