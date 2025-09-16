#include "headers.h"

extern char prev_dir[4096];
extern int foreground_pid;
extern char foreground[4096];
extern Queue head;
extern char home_dir[4096];

void ping(char* input)
{
    // printf("%s",input);
    char pidstring[100];
    int i=5;
    while(input[i]!=' ')
    {
        pidstring[i-5]=input[i];
        i++;
    }
    pidstring[i-5]='\0';
    // printf("%s\n",pidstring);
    int pid=convert_to_int(pidstring);
    // printf("%d\n",pid);
    i++;
    int j=0;
    while(input[i]!='\0')
    {
        pidstring[j++]=input[i];
        i++;
    }
    pidstring[j]='\0';
    // printf("%s\n",pidstring);
    int signal=convert_to_int(pidstring);
    // printf("%d\n",signal);
    signal=signal%32;
    if(pid<=0)
    {
        printf("pid invalid!!\n");
        return;
    }
    int k=kill(pid,signal);
    if(k==-1)
    {
        printf("No such process found\n");
    }
    else
    {
        printf("Sent signal %d to process with pid %d\n",signal,pid);
    }
}

void sighandler()
{
    if(foreground_pid!=-1)
    {
        kill(foreground_pid,SIGINT);
        printf("\n");
    }
    // else
    // {
        // prompt(home_dir);
    // }
}

void CTRLD()
{
    kill(0,SIGTERM);
    exit(0);
}

void sigstopper()
{
    if(foreground_pid!=-1)
    {
        // printf("%d\n",foreground_pid);
        printf("\n");
        tcsetpgrp(STDIN_FILENO, getpgrp());
        kill(foreground_pid,SIGTSTP);
        if(find_by_val(head,foreground_pid)==0)     //if not in queue
            Push(head,foreground_pid,foreground);
    }
    else
    {
        printf("\n");
        prompt(home_dir);
        return;
    }
}