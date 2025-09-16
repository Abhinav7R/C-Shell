#include "headers.h"

extern char prev_dir[4096];

void bg(char* input)
{
    // printf("%s",input);
    char pidstring[100];
    int i=3;
    while(input[i]!='\0')
    {
        pidstring[i-3]=input[i];
        i++;
    }
    pidstring[i-3]='\0';
    // printf("%s\n",pidstring);
    int pid=convert_to_int(pidstring);
    printf("%d\n",pid);
    if(kill(pid,SIGCONT)==-1)      //continue error
    {
        printf("No such process found\n");
    }
    // else
    // {
    //     printf("hi\n");
    // }
    
}