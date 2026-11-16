#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

void
cpu_work(void)
{
volatile int x=0;

for(int i=0;i<50000000;i++)
x+=i;
}

void
delay(void)
{
volatile int x=0;

for(int i=0;i<10000000;i++)
x+=i;
}

int 
main(void)
{
int p1,p2,p3;
p1=fork();

if(p1==0){
cpu_work();
printf("PID %d complleted\n",getpid());
exit(0);
}

delay();

p2=fork();

if(p2==0){
cpu_work();
printf("PID %d completed\n",getpid());
exit(0);
}

delay();

p3=fork();

if(p3==0){
cpu_work();
printf("PID %d completed\n",getpid());
exit(0);
}
wait(0);
wait(0);
wait(0);

exit(0);
}
