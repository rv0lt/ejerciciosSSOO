#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main(int argc, char*argv[])
{
    int fd[2]; /*pipe*/
    pid_t pid;
    char c[] = {'1','2','3'};
    char buf[1];
    pid_t p0 = getpid();
    if(pipe(fd)<0){
        perror("error pipe");
        return -1;
            }//pipe
    for(int i=0; i<2; i++)
    {
        pid=fork();
        switch(pid){
            case -1:
                perror("fork");
                exit(1);
            case 0:
                /*proceso hijo*/
                close(fd[0]);
                write(fd[1],&c[i],1 );
                close(fd[1]);
            default:
                close(fd[1]);
                wait(NULL);
                if(p0 == getpid()){
                read(fd[0], buf, 1);
                fprintf(stdout, buf);
                }//if
                close(fd[0]);
                exit(1);
                break;

        }//switch
    }//for
    return 0;

}