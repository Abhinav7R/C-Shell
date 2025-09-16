#include "headers.h"

char prev_dir[4096];
int foreground_pid=-1;
char foreground[4096];
Queue head;
char home_dir[4096];

int main()
{
    head =(Queue)malloc(sizeof(Q));
    head->val=0;
    head->name=NULL;
    head->previous=NULL;
    head->next=NULL;

    prev_dir[0]='\0';               //to check initial value of prev_dir

    char* cwd=(char*)malloc(sizeof(char)*4096);
    cwd=findcwd();
    strcpy(home_dir,cwd);
    // printf("current directory %s",cwd);

    signal(SIGINT,sighandler);
    signal(SIGTSTP,sigstopper);

    // Keep accepting commands
    while (1)
    {
        // //check if the new foreground process was put in background by CTRL+Z
        // check_fg(head,foreground,foreground_pid);
        check_bg(head);
        // Print appropriate prompt with username, systemname and directory before accepting input
        prompt(cwd);
        char input[4096];
        char* checknull=fgets(input, 4096, stdin);
        
        char* command_to_store=(char*)malloc(sizeof(char)*4096);
        command_to_store=make_good(input);
        store_command(command_to_store, cwd);                   //pastevents

        if(checknull==NULL)     //CTRL+D
        {
            CTRLD();
        }
        int flag=execute(input,head,cwd);

        if(flag==1)
        {
            continue;
        }
        // while(token!=NULL)
        // {
        //     // printf("%s\n",token);
        //     token=strtok(NULL,delimiters);
        //     task=which_task(token);
        //     switch (task)
        //     {
        //     case 3:
        //         warp(token);
        //         break;
            
        //     default:
        //         break;
        //     }
        // }
    }
}
