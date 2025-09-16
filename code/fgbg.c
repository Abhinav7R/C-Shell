#include "headers.h"

extern char prev_dir[4096];
extern int foreground_pid;
extern char foreground[4096];

void fgbg(char* input, Queue head)

{
    // printf("%s\n",input);
    if(input[strlen(input)-1]=='&')
    {
        //background process
        char newinput[100];
        strncpy(newinput,input,strlen(input)-1);
        newinput[strlen(input)-1]='\0';
        char* good_input=check_correctness(newinput);
        // printf("%s",good_input);
        // ##################################################################
        
        // int status;
        int child_pid=fork();
        // time_t start = time(NULL);
        char** commands=(char**)malloc(sizeof(char*)*10);
        for(int i=0;i<10;i++)
        {
            commands[i]=(char*)malloc(sizeof(char)*100);
            // commands[i]=NULL;
        }

        if(child_pid==-1)
        {
            printf("error in fork!!\n");
            return;
        }
        else if(child_pid==0)
        {
            //child process
            //execvp code
            
            
            int command_index=0;
            char delimit[]=" ";
            char* token=strtok(good_input,delimit);
            while(token!=NULL)
            {
                strcpy(commands[command_index++],token);
                token=strtok(NULL,delimit);
            }
            commands[command_index]=NULL;


            execvp(commands[0],commands);
            perror("Exec failed");

            // printf("hello2\n");

        }
        else if(child_pid>0)
        {
            // printf("parent %d\n",child_pid);
            //parent process
            printf("%d\n",child_pid);
            // waitpid(child_pid,&status,0);
            // time_t end = time(NULL);
            // time_t time_taken = end - start;
            // if(time_taken>2)
            //     printf("%s took %ld seconds\n",input,time_taken);
            // char* name_to_push=(char*)malloc(sizeof(char)*4096);
            // strcpy(name_to_push,commands[0]);
            // printf("pushed %s",commands[0]);
            Push(head,child_pid,good_input);
        
        }
        // ##################################################################

    }
    else
    {
        
        strcpy(foreground,input);
        //foreground process
        // printf("%s",input);
        // time_t start = time(NULL); 
        // system(input);
        // time_t end = time(NULL);
        // time_t time_taken = end - start;
        // if(time_taken>2)
        //     printf("%s took %ld seconds\n",input,time_taken);
        int status;
        int child_pid=fork();
        time_t start = time(NULL);
        if(child_pid==-1)
        {
            printf("error in fork!!\n");
            return;
        }
        else if(child_pid==0)
        {
            //child process
            //execvp code
            
            char** commands=(char**)malloc(sizeof(char*)*10);
            for(int i=0;i<10;i++)
            {
                commands[i]=(char*)malloc(sizeof(char)*100);
                // commands[i]=NULL;
            }
            int command_index=0;
            char delimit[]=" ";
            char* token=strtok(input,delimit);
            while(token!=NULL)
            {
                strcpy(commands[command_index++],token);
                token=strtok(NULL,delimit);
            }
            commands[command_index]=NULL;

            // int ii=0;
            // int command_index=0;
            // int h=0;
            // while(input[h]!='\0')
            // {
            //     if(input[h]==' ')
            //     {
            //         commands[command_index][++ii]='\0';
            //         command_index++;
            //         ii=0;
            //         h++;
            //     }
            //     commands[command_index][ii++]=input[h];
            //     h++;
            // }
            // // printf("index %d\n",command_index);
            // commands[command_index][ii]='\0';
            // commands[++command_index]=NULL;
            
            // for(int i=0;i<10;i++)
            // {
            //     // printf("%d ",i);
            //     if(commands[i]!=NULL)
            //         printf("%s\n",commands[i]);
            //     else
            //     break;
            // }

            // printf("a %s a",commands[2]);
            // printf("hello\n");

            execvp(commands[0],commands);
            perror("Exec failed");

            // printf("hello2\n");

        }
        else if(child_pid>0)
        {
            foreground_pid=child_pid;
            // printf("parent %d\n",child_pid);
            //parent process
            // printf("%d",child_pid);
            waitpid(child_pid,&status,WUNTRACED);
            time_t end = time(NULL);
            time_t time_taken = end - start;
            if(time_taken>2)
                printf("%s took %ld seconds\n",input,time_taken);
        
        }
    }
}

void check_bg(Queue head)
{
    int n=head->val;
    while(n--)
    {
        poppedelement popped=Pop(head);
        int status=0;
        int pid=popped.val;
        char* name=popped.name;
        // printf("%d %s\n",pid,name);
        int w=waitpid(pid,&status,WNOHANG);
        if(!w)
        {
            //process still going on
            Push(head,pid,name);
        }
        else
        {
            //process over
            if(WIFEXITED(status))
            {
                //successful
                printf("%s exited normally (%d)\n",name,pid);
            }
            else
            {
                //unsuccessful
                printf("%s exited abnormally (%d)\n",name,pid);
            }
        }
    }
}