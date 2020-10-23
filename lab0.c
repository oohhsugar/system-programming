#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
int main(int argc, char *argv[])
{
pid_t pid;
int rv; 
switch(pid=fork()) {
case -1:
perror("fork");
exit(1);
case 0:
printf(" CHILD: Это процесс - потомок!\n"); 
execvp (argv[1], &argv[1]); 
exit(1);
default:
printf("PARENT: Это процесс-родитель!\n");
wait(&rv);
printf("EXITCODE = %d\n", WEXITSTATUS(rv));
}
return(0);
}
