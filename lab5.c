#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <ctype.h>

int main(int argc, char ** argv) {
printf("program started\n");

int fd[2];
if (pipe(fd) == -1) { perror("pipe creating error: "); exit(1); }
printf("pipe created:\n fd[0]: %d\n fd[1]: %d\n", fd[0], fd[1]);

int childid;
switch(childid = fork())
{
case -1:
perror("fork error: ");
return 1;

case 0:
printf("Output process started\n");
//close(myPipe[1]);
printf("Output process pipe end:%d\n", fd[0]);
char ch;
ssize_t ret;
while (ret = read(fd[0], &ch, 1) >= 0)
{
printf("%c",toupper(ch)); //принимает данные из трубы
fflush(stdout);
}
if(ret == -1)
{
perror("pipe output error: ");
exit(1);
}
break;

///////////////////////////////////////

default:
printf("Input process started\n");
//close(myPipe[0]);
printf("Input process pipe end:%d\n", fd[1]); //отправляет данные в трубу
char str[] = "aaaaaaaaaaAaaaaaaaa";
write(fd[1],str,strlen(str));
sleep(3);
strcpy(str,"_bbbBbb");
write(fd[1],str,strlen(str));
break;
}
return 0;
}
