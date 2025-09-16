#include "headers.h"

extern char prev_dir[4096];

char* findcwd()
{
    //cwd current working directory
    // int current_dir;
    char* cwd=(char*)malloc(sizeof(char)*4096);
    if(getcwd(cwd,4096)==NULL)
    {
        printf("Error in getcwd!");
        exit(1);
    }
    // printf("%s",cwd);
    return cwd;
}

void prompt(char* home_dir) {
    // Do not hardcode the prmopt
    // printf("<Everything is a file> "); 

    //host or system
    int hostname;                                   //return value of gethostname
    int namesize=256;                               //restricted to 255 generally
    char host[namesize];                            //char array <host> will hold the name
    hostname=gethostname(host,namesize);
    if(hostname==-1)                                //in case of failure
    {
        printf("Error in gethostname!");
        exit(1);
    }

    //username
    int username;
    char user[namesize];                            //to hold username
    username=getlogin_r(user,namesize);             //returns 0 on success else non zero
    if(username!=0)                                 //in case of failure
    {
        printf("Error in getusername!");
        exit(1);
    }

    //cwd current working directory
    char cwd[4096];
    if(getcwd(cwd,4096)==NULL)
    {
        printf("Error in getcwd!");
        exit(1);
    }
    
    //check if it is a subdir of the current dir
    int cwd_length=strlen(cwd);
    int flag=0;
    int i=0;
    for(i=0;i<cwd_length;i++)
    {
        if(home_dir[i]!=cwd[i])
        {
            flag=1;
            break;
        }
    }
    if(flag==0)
    {
        if(strlen(cwd)<strlen(home_dir))
        {
            flag=1;
        }
    }
    char dir_name_to_print[4096];
    if(flag==0)
    {
        //then cwd is sub directory of home directory
        int j=0;
        dir_name_to_print[j++]='~';
        while(cwd[i]!='\0')
        {
            dir_name_to_print[j]=cwd[i];
            i++;
            j++;
        }
        dir_name_to_print[j]='\0';
    }

    else if(flag==1)
    {
        //then its some other directory
        strcpy(dir_name_to_print,cwd);
    }

    int home_dir_length=strlen(home_dir);
    if(strncmp(home_dir,dir_name_to_print,home_dir_length)==0)
    {
        char final_dir_name[4096];
        final_dir_name[0]='~';
        int index=home_dir_length;
        for(int i=index;i<strlen(dir_name_to_print);i++)
        {
            final_dir_name[i-index+1]=dir_name_to_print[i];
        }
        strcpy(dir_name_to_print,final_dir_name);
    }

    printf("\033[1;31m<%s@%s:%s>\033[1;0m",user,host,dir_name_to_print);             //print system name in different colour
}
