#include <stdio.h>
#include <signal.h>
# include <stdlib.h>

void hand(int sig){
int pid = getpid();

printf("\ncaught div by zero in : %d", pid);
exit(0);
}


void main(){
int num = 0;
signal(SIGFPE, hand);
num = 9/0;
printf("Hello \n");
}