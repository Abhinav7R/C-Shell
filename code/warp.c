#include "headers.h"

extern char prev_dir[4096];

void warp(char* input, char* home_dir)
{
    if(strcmp("warp",input)==0)
    {
        strcpy(prev_dir,findcwd());
        chdir(home_dir);
        printf("%s\n",home_dir);
        return;
    }
    char delimit[]=" ";
    char* individual=strtok(input,delimit);     //to remove the warp and space after it 
    //needs to be put in a loop
    individual=strtok(NULL,delimit);
    while(individual!=NULL)
    {
    if(individual[0]=='~')
    {
        strcpy(prev_dir,findcwd());
        // chdir(home_dir);
        char tildafinal[4096];
        strcpy(tildafinal,home_dir);
        strcat(tildafinal,individual+1);
        chdir(tildafinal);
        printf("%s\n",tildafinal);
    }
    else if(individual[0]=='.'&&individual[1]!='.')
    {
        char* cwd=findcwd();
        printf("%s\n",cwd);
        strcpy(prev_dir,cwd);
        chdir(individual);
    }
    else if(individual[0]=='.'&&individual[1]=='.')
    {
        strcpy(prev_dir,findcwd());
        chdir(individual);
        char* cwd=findcwd();
        printf("%s\n",cwd);
    }
    else if(individual[0]=='-')
    {
        if(prev_dir[0]=='\0')
        {
            printf("old pwd not set!!\n");
            individual=strtok(NULL,delimit);
            continue;
        }
        char temp[4096];
        strcpy(temp,findcwd());
        chdir(prev_dir);
        strcpy(prev_dir,temp);
        char* cwd=findcwd();
        printf("%s\n",cwd);
    }
    else
    {
        //absolute or relative path
        if(individual[0]=='/')
        {
            // printf("%s",individual);
            strcpy(prev_dir,findcwd());
            int k=chdir(individual);
            if(k==-1)
            {
                printf("No such directory exists\n");
                return;
            }
            char* cwd=findcwd();
            printf("%s\n",cwd);
        }
        else
        {
            strcpy(prev_dir,findcwd());
            int k=chdir(individual);
            if(k==-1)
            {
                printf("No such directory exists\n");
                return;
            }
            char* cwd=findcwd();
            printf("%s\n",cwd);
        }
    }
    individual=strtok(NULL,delimit);
    }
}