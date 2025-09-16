#include "headers.h"

extern char prev_dir[4096];

void printdirs(char* cwd, char* home_dir, int aflag, int lflag)
{
    struct dirent **namelist;
    int n;
    n = scandir(cwd, &namelist, NULL, alphasort);
    if (n == -1) 
    {
        perror("scandir error\n");
        // exit(EXIT_FAILURE);
        return;
    }
    int i=0;
    if(lflag==0 && aflag==0)
    {
        while (i!=n) 
        {
            if(namelist[i]->d_name[0]!='.')
            {
                if(namelist[i]->d_type !=4)   //files
                {
                    // executible
                    struct stat sb;
                    if(stat(namelist[i]->d_name, &sb) == 0 && sb.st_mode & S_IXUSR)
                    {
                        printf("\033[1;32m%s\033[1;0m\n", namelist[i]->d_name);
                    }
                    else
                    {
                        printf("\033[1;37m%s\033[1;0m\n", namelist[i]->d_name);
                    }
                }
                else if(namelist[i]->d_type== 4)   //directory
                {
                    printf("\033[1;34m%s\033[1;0m\n", namelist[i]->d_name);
                }
                free(namelist[i]);
            }
            i++;
        }
    }
    
    else if(lflag==0 && aflag==1)
    {
        while (i!=n) 
        {
            // if(namelist[i]->d_name[0]!='.')
            // {
                if(namelist[i]->d_type !=4)   //files
                {
                    // executible
                    struct stat sb;
                    if(stat(namelist[i]->d_name, &sb) == 0 && sb.st_mode & S_IXUSR)
                    {
                        printf("\033[1;32m%s\033[1;0m\n", namelist[i]->d_name);
                    }
                    else
                    {
                        printf("\033[1;37m%s\033[1;0m\n", namelist[i]->d_name);
                    }
                }
                else if(namelist[i]->d_type== 4)   //directory
                {
                    printf("\033[1;34m%s\033[1;0m\n", namelist[i]->d_name);
                }
                free(namelist[i]);
            // }
            i++;
        }
    }
    
    else if(lflag==1 && aflag==0)
    {
        int j=0;
        int sizebytes=0;
        while(j!=n)
        {
            struct stat mystruct_dummy;
            stat(namelist[j]->d_name,&mystruct_dummy);
            if(namelist[j]->d_name[0]!='.')
                sizebytes+=mystruct_dummy.st_blocks;
            // printf("%ld ",mystruct_dummy.st_blocks);
            j++;
        }
        printf("total %d\n",sizebytes/2);               //confirmed with terminal ls -la -s its half
        while (i!=n) 
        {
            struct stat mystruct;
            stat(namelist[i]->d_name,&mystruct);
            if(namelist[i]->d_name[0]!='.')
            {
                // file
                if(S_ISREG(mystruct.st_mode))
                {
                    printf("-");
                }
                // dir
                if(S_ISDIR(mystruct.st_mode))
                {
                    printf("d");
                }
                // link
                if(S_ISLNK(mystruct.st_mode))
                {
                    printf("l");
                }

                //user permissions
                if(S_IRUSR & mystruct.st_mode)
                    printf("r");
                else
                    printf("-");
                if(S_IWUSR & mystruct.st_mode)
                    printf("w");
                else
                    printf("-");
                if(S_IXUSR & mystruct.st_mode)
                    printf("x");
                else
                    printf("-");        
                //grp permissions
                if(S_IRGRP & mystruct.st_mode)
                    printf("r");
                else
                    printf("-");
                if(S_IWGRP & mystruct.st_mode)
                    printf("w");
                else
                    printf("-");
                if(S_IXGRP & mystruct.st_mode)
                    printf("x");
                else
                    printf("-");
                //others permissions
                if(S_IROTH & mystruct.st_mode)
                    printf("r");
                else
                    printf("-");
                if(S_IWOTH & mystruct.st_mode)
                    printf("w");
                else
                    printf("-");
                if(S_IXOTH & mystruct.st_mode)
                    printf("x");
                else
                    printf("-");    

                //hard links
                printf(" %4lu ",mystruct.st_nlink);

                printf("%10s ",getpwuid(mystruct.st_uid)->pw_name);
                printf("%10s ",getgrgid(mystruct.st_gid)->gr_name);

                printf("%10ld ",mystruct.st_size);

                struct timespec ts=mystruct.st_mtim;
                struct tm* mytime=localtime(&ts.tv_sec);
                char date[100];
                strftime(date,99,"%b %e %H:%M",mytime);
                printf("%s ",date);
                if(namelist[i]->d_type !=4)   //files
                {
                    // executible
                    struct stat sb;
                    if(stat(namelist[i]->d_name, &sb) == 0 && sb.st_mode & S_IXUSR)
                    {
                        printf("\033[1;32m%s\033[1;0m\n", namelist[i]->d_name);
                    }
                    else
                    {
                        printf("\033[1;37m%s\033[1;0m\n", namelist[i]->d_name);
                    }
                }
                else if(namelist[i]->d_type== 4)   //directory
                {
                    printf("\033[1;34m%s\033[1;0m\n", namelist[i]->d_name);
                }
            }
            free(namelist[i]);
            i++;
        }
    }
    
    else if(lflag==1 && aflag==1)
    {
        int j=0;
        int sizebytes=0;
        while(j!=n)
        {
            struct stat mystruct_dummy;
            stat(namelist[j]->d_name,&mystruct_dummy);
            sizebytes+=mystruct_dummy.st_blocks;
            // printf("%ld ",mystruct_dummy.st_blocks);
            j++;
        }
        printf("total %d\n",sizebytes/2);               //confirmed with terminal ls -la -s its half
        while (i!=n) 
        {
            struct stat mystruct;
            stat(namelist[i]->d_name,&mystruct);
            // file
            if(S_ISREG(mystruct.st_mode))
            {
                printf("-");
            }
            // dir
            if(S_ISDIR(mystruct.st_mode))
            {
                printf("d");
            }
            // link
            if(S_ISLNK(mystruct.st_mode))
            {
                printf("l");
            }

            //user permissions
            if(S_IRUSR & mystruct.st_mode)
                printf("r");
            else
                printf("-");
            if(S_IWUSR & mystruct.st_mode)
                printf("w");
            else
                printf("-");
            if(S_IXUSR & mystruct.st_mode)
                printf("x");
            else
                printf("-");        
            //grp permissions
            if(S_IRGRP & mystruct.st_mode)
                printf("r");
            else
                printf("-");
            if(S_IWGRP & mystruct.st_mode)
                printf("w");
            else
                printf("-");
            if(S_IXGRP & mystruct.st_mode)
                printf("x");
            else
                printf("-");
            //others permissions
            if(S_IROTH & mystruct.st_mode)
                printf("r");
            else
                printf("-");
            if(S_IWOTH & mystruct.st_mode)
                printf("w");
            else
                printf("-");
            if(S_IXOTH & mystruct.st_mode)
                printf("x");
            else
                printf("-");    

            //hard links
            printf(" %4lu ",mystruct.st_nlink);

            printf("%10s ",getpwuid(mystruct.st_uid)->pw_name);
            printf("%10s ",getgrgid(mystruct.st_gid)->gr_name);

            printf("%10ld ",mystruct.st_size);

            struct timespec ts=mystruct.st_mtim;
            struct tm* mytime=localtime(&ts.tv_sec);
            char date[100];
            strftime(date,99,"%b %e %H:%M",mytime);
            printf("%s ",date);
            if(namelist[i]->d_type !=4)   //files
            {
                // executible
                struct stat sb;
                if(stat(namelist[i]->d_name, &sb) == 0 && sb.st_mode & S_IXUSR)
                {
                    printf("\033[1;32m%s\033[1;0m\n", namelist[i]->d_name);
                }
                else
                {
                    printf("\033[1;37m%s\033[1;0m\n", namelist[i]->d_name);
                }
            }
            else if(namelist[i]->d_type== 4)   //directory
            {
                printf("\033[1;34m%s\033[1;0m\n", namelist[i]->d_name);
            }
            free(namelist[i]);
            i++;
        }
    }

    free(namelist);

    return;
}

void peek(char* input, char* home_dir)
{
    int aflag=0;
    int lflag=0;
    if(strcmp("peek",input)==0)
    {
        printdirs(findcwd(),home_dir,0,0);
        return;
    }

    // char delimit[]=" ";
    // printf("%s\n",input);
    // char* individual=strtok(input,delimit);     //to remove the peek and space after it 
    //needs to be put in a loop
    // individual=strtok(NULL,delimit);
    // while(individual!=NULL)
    // {
    char* individual=input+5; 
    // printf("%s\n",individual);   
    if(individual[0]=='~')
    {
        char tildafinal[4096];
        strcpy(tildafinal,home_dir);
        strcat(tildafinal,individual+1);
        printdirs(tildafinal,home_dir,0,0);
    }
    else if(individual[0]=='.'&&individual[1]!='.')
    {
        char* cwd=findcwd();
        printdirs(cwd,home_dir,0,0);
    }
    else if(individual[0]=='.'&&individual[1]=='.')
    {
        printdirs(individual,home_dir,0,0);
    }
    else if(individual[0]=='-')
    {
        // printf("flag to be handled\n");
        // printf("%s\n",individual);
        char path[4096];
        //-a
        if(individual[1]=='a')
        {
            aflag=1;
            if(individual[2]=='\0')
            {
                strcpy(path,findcwd());
            }
            else if(individual[2]=='l')
            {
                lflag=1;
                if(individual[3]=='\0')
                {
                    strcpy(path,findcwd());
                }
                else
                {
                    strcpy(path,individual+4);
                }
            } 
            else if(individual[2]==' ')
            {
                if(individual[3]=='-'&&individual[4]=='l')
                {
                    lflag=1;
                    if(individual[5]=='\0')
                    {
                        strcpy(path,findcwd());
                    }
                    else
                    {
                        strcpy(path,individual+6);
                    }
                }
                else
                {
                    strcpy(path,individual+3);
                }
            }   
        }
        //-l
        if(individual[1]=='l')
        {
            lflag=1;
            if(individual[2]=='\0')
            {
                strcpy(path,findcwd());
            }
            else if(individual[2]=='a')
            {
                aflag=1;
                if(individual[3]=='\0')
                {
                    strcpy(path,findcwd());
                }
                else
                {
                    strcpy(path,individual+4);
                }
            } 
            else if(individual[2]==' ')
            {
                if(individual[3]=='-'&&individual[4]=='a')
                {
                    aflag=1;
                    if(individual[5]=='\0')
                    {
                        strcpy(path,findcwd());
                    }
                    else
                    {
                        strcpy(path,individual+6);
                    }
                }
                else
                {
                    strcpy(path,individual+3);
                }
            }   
        }
        
        printdirs(path,home_dir,aflag,lflag);
        
    }
    else
    {
        //absolute or relative path
        if(individual[0]=='/')
        {
            printdirs(individual,home_dir,0,0);
        }
        else
        {
            printdirs(individual,home_dir,0,0);
        }
    }
    // individual=strtok(NULL,delimit);
    // }
}