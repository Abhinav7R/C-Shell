#include "headers.h"

extern char prev_dir[4096];
extern char home_dir[4096];
extern Queue head;

int redirect_input(const char *filename) 
{
    int input_fd = open(filename, O_RDONLY);
    if (input_fd == -1) 
    {
        printf("No such input file found!\n");
        return -1;
    }
    dup2(input_fd, STDIN_FILENO);
    close(input_fd);
    return 0;
}

int redirect_output(const char *filename, int append) 
{
    int output_fd;
    if (append==1) 
    {
        output_fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
    } 
    else 
    {
        output_fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    }

    if (output_fd == -1) 
    {
        printf("Error opening output file\n");
        return -1;
    }

    dup2(output_fd, STDOUT_FILENO);
    close(output_fd);
    return 0;
}

int io(char* input, Queue head)
{
    int input_copy=dup(STDIN_FILENO);
    int output_copy=dup(STDOUT_FILENO);

    // int child_pid=fork();
    // if(child_pid==0)
    // {
    char inputcopy[4096];
    strcpy(inputcopy,input);  

    if (strstr(input, "<") != NULL) 
    {
        char *inputfilename = strtok(input, "<");
        // printf("..%s\n",inputfilename);
        inputfilename = strtok(NULL, "<");
        // printf("..%s\n",inputfilename);
        inputfilename = strtok(inputfilename, " \t");
        // printf("..%s\n",inputfilename);
        if (inputfilename != NULL) 
        {
            int k=redirect_input(inputfilename);
            if(k==-1)                               //input file not found
            {
                return -1;
            }
        }
    }
    strcpy(input,inputcopy);
    // printf("%s\n",input); 
    if (strstr(input, ">>") != NULL) 
    {
        char *outputfile = strtok(input, ">");
        // printf("%s\n",outputfile);
        outputfile = strtok(NULL, ">");
        // printf("%s\n",outputfile);
        outputfile = strtok(outputfile, " \t");
        // printf("%s\n",outputfile);
        if (outputfile != NULL) 
        {
            // printf("oh");
            int k=redirect_output(outputfile, 1);
            if(k==-1)                               //input file not found
            {
                return -1;
            }
        }
    } 
    strcpy(input,inputcopy);
    if (strstr(input, ">") != NULL && strstr(input, ">>") == NULL) 
    {
        char *outputfile = strtok(input, ">");
        // printf("%s\n",outputfile);
        outputfile = strtok(NULL, " \t");
        // printf("%s\n",outputfile);
        if (outputfile != NULL) 
        {
            int k=redirect_output(outputfile, 0);
            if(k==-1)                               //input file not found
            {
                return -1;
            }
        }
    }
    strcpy(input,inputcopy);
    char just_input[4096];
    int p=0;
    while(input[p]!='>'&&input[p]!='<')
    {
        just_input[p]=input[p];
        p++;
    }
    just_input[p]='\0';
    execute(just_input,head,home_dir);
    dup2(input_copy,STDIN_FILENO);
    dup2(output_copy,STDOUT_FILENO);
    // exit(1);
    // char *args[4096];
    // char *token = strtok(just_input, " \t");
    // int i = 0;
    // while (token != NULL) {
    //     args[i++] = token;
    //     token = strtok(NULL, " \t");
    // }
    // args[i] = NULL;

    // execvp(args[0], args);
    // perror("Execvp failed");
    // // exit(EXIT_FAILURE);
    // return -1;
    // }
    // else if(child_pid>0)
    // {
    //     int stat;
    //     waitpid(child_pid,&stat,WUNTRACED);
    // }
    // else
    // {
    //     printf("forking error!!\n");
    //     return -1;
    // }
    return 0;    
}

int check_pipe_validity(char* input)
{
    // printf("%s\n",input);
    char new[4096];
    int i=0;
    int j=0;
    while(input[i]!='\0')
    {
        if(input[i]!=' '&&input[i]!='\t'&&input[i]!='\n')
        {
            new[j++]=input[i];
        }
        i++;
    }
    new[j]='\0';
    // printf("%s\n",new);
    if(new[0]=='|'||new[strlen(new)-1]=='|')
    {
        return 0;
    }
    for(int k=0;k<strlen(new)-1;k++)
    {
        if(new[k]=='|'&&new[k+1]=='|')
            return 0;
    }
    return 1;
}

void iopipe(char* input, Queue head)
{
    char my_input_copy[4096];
    strcpy(my_input_copy,input);
    // printf("%s\n",input);
    if(strstr(input,"|")==0)
    {
        io(input,head);
        return;
    }

    // char delimiters[]="|";
    // pipe()

    char *pipe_commands[100];
    int num_processes = 0;
    char* save_ptr;
    char *token = strtok_r(input, "|",&save_ptr);
    while (token != NULL) 
    {
        pipe_commands[num_processes++] = token;
        token = strtok_r(NULL, "|",&save_ptr);
    }
    // int j=0;
    // while(j<num_processes)
    // {
    //     printf("%s\n",pipe_commands[j]);
    //     j++;
    // }
    if (num_processes < 2) 
    {
        printf("Invalid use of pipe\n");
        return;
    }
    if((check_pipe_validity(my_input_copy))==0)
    {
        printf("Invalid use of pipe\n");
        return;
    }

    int input_copy=dup(STDIN_FILENO);
    int output_copy=dup(STDOUT_FILENO);
    int i;
    for (i = 0; i < num_processes; i++) 
    {
        int pipes[2];               //pipes[0] will be input pipes[1] output
        pipe(pipes);
        int child_pid=fork();
        if(child_pid<0)
        {
            printf("forking error\n");
        }
        else if(child_pid>0)
        {
            //parent
            close(pipes[1]);
            int stat;
            waitpid(child_pid,&stat,WUNTRACED);

            if(i==num_processes-1)
            {
                dup2(input_copy,STDIN_FILENO);
                close(input_copy);
            }    
            else    
                dup2(pipes[0],STDIN_FILENO);
            close(pipes[0]);
        }
        else
        {
            //child
            close(pipes[0]);
            if(i==num_processes-1)
            {
                dup2(output_copy,STDOUT_FILENO);
                close(output_copy);
            }
            else    
                dup2(pipes[1],STDOUT_FILENO);
            close(pipes[1]);
            execute(pipe_commands[i],head,home_dir);  
            exit(0);  
        }
        
    }

    return ;
}







