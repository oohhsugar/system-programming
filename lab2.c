#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/io.h>
#include <unistd.h>
#include <sys/mman.h>

void arrpush(int *arr, int index, int value, int *size, int *capacity)
{
if (*size > *capacity)
{
realloc(arr, sizeof(arr) * 2);
*capacity = sizeof(arr) * 2; 
}
arr[index] = value;
*size = *size + 1;
}

int main(int argc, char *argv[])
{
int arrSize = 0;
int arrCap = 2;
int *arr = malloc(arrCap * sizeof(int));

int indexarrxSize = 0;
int indexarrCap = 2;
int *indexarr = malloc(indexarrCap * sizeof(int));

char ch;
int strCount = 0;
int enterCount = 0;
int strNumToPrint = 1;
off_t offsetToPrint;
ssize_t ret;
struct stat filestat;
printf("Путь к файлу указывается как аргумент при запуске \nПопытка открыть файл %s \n", argv[1]);
int filedesc = open(argv[1], 00);
if (filedesc < 0)
{
perror("Ошибка открытия файла:");
return 1;// то неудача
}
if(fstat(filedesc,&filestat)<0)
{
perror("stat error");
return 1;
}

char *mmapptr = mmap(NULL,filestat.st_size,PROT_READ,MAP_SHARED,filedesc,0);
if(mmapptr == MAP_FAILED)
{
perror("mmap error");
return 0;
}
close(filedesc);

for (int i=0;i<=filestat.st_size / sizeof(char);i++)
{
strCount++;
if (mmapptr[i] == '\n')
{
enterCount++;
arrpush(indexarr,enterCount,strCount + (indexarr[enterCount-1] ?: 0),&indexarrxSize,&indexarrCap);
arrpush(arr, enterCount, strCount, &arrSize, &arrCap);
printf("Строка %d , символов %d \n", enterCount, strCount);
strCount = 0;
}
}

while(strNumToPrint!=0)
{
printf("\nВсего строк: %d\n Введите номер требуемой для вывода строки(0 для выхода):", enterCount);
scanf("%d", &strNumToPrint);

offsetToPrint = indexarr[strNumToPrint-1];

for (int i = 0; i < arr[strNumToPrint]-1; i++)
{
ch = mmapptr[i+offsetToPrint];
printf("%c", ch);
}
}

printf("Завершение программы \n");
return 0;
}
