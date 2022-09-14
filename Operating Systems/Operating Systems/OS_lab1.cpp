#include<stdio.h>
#include<unistd.h>

int main(){

    int pid;
    
    printf("Im original process with PID %d and PPID %d. \n", getpid(), getppid());

    pid = fork();

    if(pid != 0){
        printf("Im parent process with PID %d and PPID %d. \n", getpid(), getppid());
        printf("My child's PID is %d \n", pid);
    }

    else{
        printf("Im child process with PID %d and PPID %d. \n", getpid(), getppid());
    }

    // fork();

    printf("PID %d TERMINATed\n", getpid());
    return 0;
}