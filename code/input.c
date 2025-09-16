#include "headers.h"

extern char prev_dir[4096];

/*
char* store_input(char* input)
{
    char* good_input=(char*)malloc(sizeof(char)*4096);                  //without spaces and tabs
    int j=0;
    int l=strlen(input);
    for(int i=0;i<l;i++)
    {
        //handling warp../warp./warp~/warp-
        if(input[i]=='w')
        {
            if(i+4<l)
            {
                if(input[i+1]=='a'&&input[i+2]=='r'&&input[i+3]=='p')
                {
                    if(input[i+4]=='.'||input[i+4]=='~'||input[i+4]=='-')
                    {
                        j=0;
                        break;
                    }
                }
            }
        }
        
        if(input[i]!=' ' && input[i]!='\t')
        {
            good_input[j++]=input[i];
        }
    }
    good_input[j]='\0';

    // printf("%s",good_input);

    return good_input;
}
*/

char* check_correctness(char* token)
{
    char* good_token=(char*)malloc(sizeof(char)*4096);
    int l=strlen(token);
    for(int i=0;i<l;i++)
    {
        //handling warp../warp./warp~/warp-
        if(token[i]=='w')
        {
            if(i+4<l)
            {
                if(token[i+1]=='a'&&token[i+2]=='r'&&token[i+3]=='p')
                {
                    if(token[i+4]=='.'||token[i+4]=='~'||token[i+4]=='-')
                    {
                        return NULL;
                    }
                }
            }
        }
        else if(token[i]=='p')
        {
            if(i+4<l)
            {
                if(token[i+1]=='e'&&token[i+2]=='e'&&token[i+3]=='k')
                {
                    if(token[i+4]=='.'||token[i+4]=='~'||token[i+4]=='-')
                    {
                        return NULL;
                    }
                }
            }
        }
    }

    int j=0;
    while(token[l-1]==' '||token[l-1]=='\t'||token[l-1]=='\n')
    {
        l--;
    }
    for(int i=0;i<l;i++)
    {   
        if(token[i]!=' ' && token[i]!='\t' && token[i]!='\n')
        {
            good_token[j++]=token[i];
        }
        if(token[i]==' ' || token[i]=='\t')
        {
            if(j!=0&&good_token[j-1]!=' ')
            {
                good_token[j++]=' ';
            }
        }
    }
    good_token[j]='\0';

    // printf("%s\n",good_token);

    return good_token;
}


int which_task(char* token)
{
    //warp 3
    if(token[0]=='w'&&token[1]=='a'&&token[2]=='r'&&token[3]=='p')
    {
        return 3;
    }    
    else if(token[0]=='p'&&token[1]=='e'&&token[2]=='e'&&token[3]=='k')
    {
        return 4;
    }
    else if(token[0]=='s'&&token[1]=='e'&&token[2]=='e'&&token[3]=='k')
    {
        return 8;
    }
    else if(token[0]=='p'&&token[1]=='r'&&token[2]=='o'&&token[3]=='c'&&token[4]=='l'&&token[5]=='o'&&token[6]=='r'&&token[7]=='e'&&(token[8]=='\0'||token[8]==' '))
    {
        return 7;
    }
    else if(token[0]=='p'&&token[1]=='a'&&token[2]=='s'&&token[3]=='t'&&token[4]=='e'&&token[5]=='v'&&token[6]=='e'&&token[7]=='n'&&token[8]=='t'&&token[9]=='s')
    {
        return 6;
    }
    else if(strcmp("activities",token)==0)
    {
        return 12;
    }
    else if(token[0]=='p'&&token[1]=='i'&&token[2]=='n'&&token[3]=='g')
    {
        return 13;
    }
    else if(token[0]=='b'&&token[1]=='g')
    {
        return 14;
    }
    else if(token[0]=='f'&&token[1]=='g')
    {
        return 17;
    }
    else if(token[0]=='i'&&token[1]=='M'&&token[2]=='a'&&token[3]=='n')
    {
        return 16;
    }
    else if(strncmp("neonate -n ",token,11)==0)
    {
        return 15;
    }
    else
    {
        return 0;
    }
}

char* make_good(char* token)
{
    char* good_token=(char*)malloc(sizeof(char)*4096);
    int l=strlen(token);
    int j=0;
    while(token[l-1]==' '||token[l-1]=='\t'||token[l-1]=='\n')
    {
        l--;
    }
    for(int i=0;i<l;i++)
    {   
        if(token[i]!=' ' && token[i]!='\t' && token[i]!='\n')
        {
            good_token[j++]=token[i];
        }
        if(token[i]==' ' || token[i]=='\t')
        {
            if(j!=0&&good_token[j-1]!=' ')
            {
                good_token[j++]=' ';
            }
        }
    }
    good_token[j]='\0';

    // printf("%s\n",good_token);

    return good_token;
}

int contains_io_pipe(char* input)
{
    int i=0;
    while(input[i]!='\0')
    {
        if(input[i]=='>'||input[i]=='<'||input[i]=='|')
        {
            return 1;
        }
        i++;
    }
    return 0;
}