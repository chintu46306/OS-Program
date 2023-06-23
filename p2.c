
/*
Write a C program for System calls of
Operating system (Fork, Getpid, Exit)
*/


#include<stdio.h>
#include<unistd.h>
#include <stdlib.h>
int main()
{
int pid,pid1,pid2;
pid=fork();
if(pid==-1)
{
printf("ERROR IN PROCESS CREATION \n");
exit(1);
}
if(pid!=0)
{
pid1=getpid();
printf("\n the parent process ID is %d", pid1);
}
else
{
pid2=getpid();
printf("\n the child process ID is %d", pid2);
}}