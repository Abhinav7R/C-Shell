#include "headers.h"

extern char prev_dir[4096];

void fg(char* input)
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
    // printf("%d\n",pid);
    if(kill(pid,0)==0)      //process exists
    {
        // printf("hi\n");
        kill(pid,SIGCONT);
        tcsetpgrp(STDIN_FILENO,getpgid(pid));    //bring process to foreground
        int status;
        waitpid(pid, &status, WUNTRACED);       // wait for it to finish
        tcsetpgrp(STDIN_FILENO, getpgrp());     // go back to original fg process
    }
    else
    {
        printf("No such process found\n");
    }
}

// void check_fg(Queue head,char* foreground, int foreground_pid)
// {
//     printf("...%d %s\n",foreground_pid,foreground);
//     int fg_grp_id=getpgid(foreground_pid);
//     int foreground_grp_id=tcgetpgrp(STDIN_FILENO);
//     printf("%d %d\n",fg_grp_id,foreground_grp_id);
//     if(fg_grp_id!=foreground_grp_id)        //put to background
//     {
//         Push(head,foreground_pid,foreground);
//     }
// }
