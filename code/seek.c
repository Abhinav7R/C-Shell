#include "headers.h"

extern char prev_dir[4096];

int count_dir_and_files(char* search, char* dir, char* home_dir, int e, int d, int f, char* givendir)
{
    int count =0;
    if(e==1 && d==0 && f==1)
    {
        struct dirent **namelist;
        int n;
        n = scandir(dir, &namelist, NULL, alphasort);
        if (n == -1) 
        {
            perror("scandir error\n");
            // exit(EXIT_FAILURE);
            return -1;
        }
        struct stat mystruct;
        int i=0;
        while(i!=n)
        {
            stat(namelist[i]->d_name,&mystruct);
            if(namelist[i]->d_name[0]!='.')
            {
                char newname[4096];
                int j=0;
                while(!(namelist[i]->d_name[j]=='.'||namelist[i]->d_name[j]=='\0'))
                {
                    newname[j]=namelist[i]->d_name[j];
                    j++;
                }
                newname[j]='\0';
                if(strcmp(newname,search)==0)
                {
                    char path_to_print[4096];
                    // char* cwd=findcwd();
                    // printf("%s",cwd);
                    int index=strlen(givendir);
                    path_to_print[0]='.';
                    int k=1;
                    while(dir[index]!='\0')
                    {
                        path_to_print[k++]=dir[index++];
                    }
                    path_to_print[k]='/';
                    path_to_print[k+1]='\0';
                    strcat(path_to_print,namelist[i]->d_name);
                    // printf("%s\n",path_to_print);
                    if(namelist[i]->d_type== 4)   //directory
                    {
                        // printf("\033[1;34m%s\033[1;0m\n", path_to_print);
                        // count++;
                    }
                    else    //files
                    {
                        // printf("\033[1;32m%s\033[1;0m\n", path_to_print);
                        count++;
                    }
                    
                }
                if(namelist[i]->d_type== 4)
                {
                    // printf("recursion here\n");
                    char newdir[4096];
                    strcpy(newdir,dir);
                    char slash[2];
                    slash[0]='/';
                    slash[1]='\0';
                    strcat(newdir,slash);
                    strcat(newdir,namelist[i]->d_name);
                    // printf("%s\n",newdir);
                    count+=count_dir_and_files(search,newdir,home_dir,e,d,f,givendir);
                }
            }
            i++;
        }
    }

    else if(e==1 && d==1 && f==0)
    {
        struct dirent **namelist;
        int n;
        n = scandir(dir, &namelist, NULL, alphasort);
        if (n == -1) 
        {
            perror("scandir error\n");
            // exit(EXIT_FAILURE);
            return -1;
        }
        struct stat mystruct;
        int i=0;
        while(i!=n)
        {
            stat(namelist[i]->d_name,&mystruct);
            if(namelist[i]->d_name[0]!='.')
            {
                char newname[4096];
                int j=0;
                while(!(namelist[i]->d_name[j]=='.'||namelist[i]->d_name[j]=='\0'))
                {
                    newname[j]=namelist[i]->d_name[j];
                    j++;
                }
                newname[j]='\0';
                if(strcmp(newname,search)==0)
                {
                    char path_to_print[4096];
                    // char* cwd=findcwd();
                    // printf("%s",cwd);
                    int index=strlen(givendir);
                    path_to_print[0]='.';
                    int k=1;
                    while(dir[index]!='\0')
                    {
                        path_to_print[k++]=dir[index++];
                    }
                    path_to_print[k]='/';
                    path_to_print[k+1]='\0';
                    strcat(path_to_print,namelist[i]->d_name);
                    // printf("%s\n",path_to_print);
                    if(namelist[i]->d_type== 4)   //directory
                    {
                        // printf("\033[1;34m%s\033[1;0m\n", path_to_print);
                        count++;
                    }
                    else    //files
                    {
                        // printf("\033[1;32m%s\033[1;0m\n", path_to_print);
                        // count++;
                    }
                    
                }
                if(namelist[i]->d_type== 4)
                {
                    // printf("recursion here\n");
                    char newdir[4096];
                    strcpy(newdir,dir);
                    char slash[2];
                    slash[0]='/';
                    slash[1]='\0';
                    strcat(newdir,slash);
                    strcat(newdir,namelist[i]->d_name);
                    // printf("%s\n",newdir);
                    count+=count_dir_and_files(search,newdir,home_dir,e,d,f,givendir);
                }
            }
            i++;
        }
    }

    else if(e==1 && d==0 && f==0)
    {
        struct dirent **namelist;
        int n;
        n = scandir(dir, &namelist, NULL, alphasort);
        if (n == -1) 
        {
            perror("scandir error\n");
            // exit(EXIT_FAILURE);
            return -1;
        }
        struct stat mystruct;
        int i=0;
        while(i!=n)
        {
            stat(namelist[i]->d_name,&mystruct);
            if(namelist[i]->d_name[0]!='.')
            {
                char newname[4096];
                int j=0;
                while(!(namelist[i]->d_name[j]=='.'||namelist[i]->d_name[j]=='\0'))
                {
                    newname[j]=namelist[i]->d_name[j];
                    j++;
                }
                newname[j]='\0';
                if(strcmp(newname,search)==0)
                {
                    char path_to_print[4096];
                    // char* cwd=findcwd();
                    // printf("%s",cwd);
                    int index=strlen(givendir);
                    path_to_print[0]='.';
                    int k=1;
                    while(dir[index]!='\0')
                    {
                        path_to_print[k++]=dir[index++];
                    }
                    path_to_print[k]='/';
                    path_to_print[k+1]='\0';
                    strcat(path_to_print,namelist[i]->d_name);
                    // printf("%s\n",path_to_print);
                    if(namelist[i]->d_type== 4)   //directory
                    {
                        // printf("\033[1;34m%s\033[1;0m\n", path_to_print);
                        count++;
                    }
                    else    //files
                    {
                        // printf("\033[1;32m%s\033[1;0m\n", path_to_print);
                        count++;
                    }
                    
                }
                if(namelist[i]->d_type== 4)
                {
                    // printf("recursion here\n");
                    char newdir[4096];
                    strcpy(newdir,dir);
                    char slash[2];
                    slash[0]='/';
                    slash[1]='\0';
                    strcat(newdir,slash);
                    strcat(newdir,namelist[i]->d_name);
                    // printf("%s\n",newdir);
                    count+=count_dir_and_files(search,newdir,home_dir,e,d,f,givendir);
                }
            }
            i++;
        }
    }

    return count;
}

int actualseek(char* search, char* dir, char* home_dir, int e, int d, int f, char* givendir)
{
    int count=0;
    // printf("%s\n",dir);
    if(e==0 && d==0 && f==0)
    {
        struct dirent **namelist;
        int n;
        n = scandir(dir, &namelist, NULL, alphasort);
        if (n == -1) 
        {
            perror("scandir error\n");
            // exit(EXIT_FAILURE);
            return -1;
        }
        struct stat mystruct;
        int i=0;
        while(i!=n)
        {
            stat(namelist[i]->d_name,&mystruct);
            if(namelist[i]->d_name[0]!='.')
            {
                char newname[4096];
                int j=0;
                while(!(namelist[i]->d_name[j]=='.'||namelist[i]->d_name[j]=='\0'))
                {
                    newname[j]=namelist[i]->d_name[j];
                    j++;
                }
                newname[j]='\0';
                if(strcmp(newname,search)==0)
                {
                    char path_to_print[4096];
                    // char* cwd=findcwd();
                    // printf("%s",cwd);
                    int index=strlen(givendir);
                    path_to_print[0]='.';
                    int k=1;
                    while(dir[index]!='\0')
                    {
                        path_to_print[k++]=dir[index++];
                    }
                    path_to_print[k]='/';
                    path_to_print[k+1]='\0';
                    strcat(path_to_print,namelist[i]->d_name);
                    // printf("%s\n",path_to_print);
                    if(namelist[i]->d_type== 4)   //directory
                    {
                        printf("\033[1;34m%s\033[1;0m\n", path_to_print);
                        count++;
                    }
                    else    //files
                    {
                        printf("\033[1;32m%s\033[1;0m\n", path_to_print);
                        count++;
                    }
                    
                }
                if(namelist[i]->d_type== 4)
                {
                    // printf("recursion here\n");
                    char newdir[4096];
                    strcpy(newdir,dir);
                    char slash[2];
                    slash[0]='/';
                    slash[1]='\0';
                    strcat(newdir,slash);
                    strcat(newdir,namelist[i]->d_name);
                    // printf("%s\n",newdir);
                    count+=actualseek(search,newdir,home_dir,e,d,f,givendir);
                }
            }
            i++;
        }
    }
    else if(e==0 && d==0 && f==1)
    {
        struct dirent **namelist;
        int n;
        n = scandir(dir, &namelist, NULL, alphasort);
        if (n == -1) 
        {
            perror("scandir error\n");
            // exit(EXIT_FAILURE);
            return -1;
        }
        struct stat mystruct;
        int i=0;
        while(i!=n)
        {
            stat(namelist[i]->d_name,&mystruct);
            if(namelist[i]->d_name[0]!='.')
            {
                char newname[4096];
                int j=0;
                while(!(namelist[i]->d_name[j]=='.'||namelist[i]->d_name[j]=='\0'))
                {
                    newname[j]=namelist[i]->d_name[j];
                    j++;
                }
                newname[j]='\0';
                if(strcmp(newname,search)==0)
                {
                    char path_to_print[4096];
                    // char* cwd=findcwd();
                    // printf("%s",cwd);
                    int index=strlen(givendir);
                    path_to_print[0]='.';
                    int k=1;
                    while(dir[index]!='\0')
                    {
                        path_to_print[k++]=dir[index++];
                    }
                    path_to_print[k]='/';
                    path_to_print[k+1]='\0';
                    strcat(path_to_print,namelist[i]->d_name);
                    // printf("%s\n",path_to_print);
                    // if(namelist[i]->d_type== 4)   //directory
                    // {
                    //     printf("\033[1;34m%s\033[1;0m\n", path_to_print);
                    //     count++;
                    // }
                    if(namelist[i]->d_type!= 4)    //files
                    {
                        printf("\033[1;32m%s\033[1;0m\n", path_to_print);
                        count++;
                    }
                    
                }
                if(namelist[i]->d_type== 4)
                {
                    // printf("recursion here\n");
                    char newdir[4096];
                    strcpy(newdir,dir);
                    char slash[2];
                    slash[0]='/';
                    slash[1]='\0';
                    strcat(newdir,slash);
                    strcat(newdir,namelist[i]->d_name);
                    // printf("%s\n",newdir);
                    count+=actualseek(search,newdir,home_dir,e,d,f,givendir);
                }
            }
            i++;
        }
    }
    else if(e==0 && d==1 && f==0)
    {
        struct dirent **namelist;
        int n;
        n = scandir(dir, &namelist, NULL, alphasort);
        if (n == -1) 
        {
            perror("scandir error\n");
            // exit(EXIT_FAILURE);
            return -1;
        }
        struct stat mystruct;
        int i=0;
        while(i!=n)
        {
            stat(namelist[i]->d_name,&mystruct);
            if(namelist[i]->d_name[0]!='.')
            {
                char newname[4096];
                int j=0;
                while(!(namelist[i]->d_name[j]=='.'||namelist[i]->d_name[j]=='\0'))
                {
                    newname[j]=namelist[i]->d_name[j];
                    j++;
                }
                newname[j]='\0';
                if(strcmp(newname,search)==0)
                {
                    char path_to_print[4096];
                    // char* cwd=findcwd();
                    // printf("%s",cwd);
                    int index=strlen(givendir);
                    path_to_print[0]='.';
                    int k=1;
                    while(dir[index]!='\0')
                    {
                        path_to_print[k++]=dir[index++];
                    }
                    path_to_print[k]='/';
                    path_to_print[k+1]='\0';
                    strcat(path_to_print,namelist[i]->d_name);
                    // printf("%s\n",path_to_print);
                    if(namelist[i]->d_type== 4)   //directory
                    {
                        printf("\033[1;34m%s\033[1;0m\n", path_to_print);
                        count++;
                    }
                    // else    //files
                    // {
                    //     printf("\033[1;32m%s\033[1;0m\n", path_to_print);
                    //     count++;
                    // }
                    
                }
                if(namelist[i]->d_type== 4)
                {
                    // printf("recursion here\n");
                    char newdir[4096];
                    strcpy(newdir,dir);
                    char slash[2];
                    slash[0]='/';
                    slash[1]='\0';
                    strcat(newdir,slash);
                    strcat(newdir,namelist[i]->d_name);
                    // printf("%s\n",newdir);
                    count+=actualseek(search,newdir,home_dir,e,d,f,givendir);
                }
            }
            i++;
        }
    }
    else if(e==0 && d==1 && f==1)
    {
        count=-1;
        printf("Invalid flags!\n");
    }
    else if(e==1 && d==1 && f==1)
    {
        count=-1;
        printf("Invalid flags!\n");
    }
    else if(e==1 && d==0 && f==0)
    {
        count=count_dir_and_files(search,dir,home_dir,e,d,f,givendir);
        if(count == 1)
        {
            struct dirent **namelist;
            int n;
            n = scandir(dir, &namelist, NULL, alphasort);
            if (n == -1) 
            {
                perror("scandir error\n");
                // exit(EXIT_FAILURE);
                return -1;
            }
            struct stat mystruct;
            int i=0;
            while(i!=n)
            {
                stat(namelist[i]->d_name,&mystruct);
                if(namelist[i]->d_name[0]!='.')
                {
                    char newname[4096];
                    int j=0;
                    while(!(namelist[i]->d_name[j]=='.'||namelist[i]->d_name[j]=='\0'))
                    {
                        newname[j]=namelist[i]->d_name[j];
                        j++;
                    }
                    newname[j]='\0';
                    if(strcmp(newname,search)==0)
                    {
                        char path_to_print[4096];
                        // char* cwd=findcwd();
                        // printf("%s",cwd);
                        int index=strlen(givendir);
                        path_to_print[0]='.';
                        int k=1;
                        while(dir[index]!='\0')
                        {
                            path_to_print[k++]=dir[index++];
                        }
                        path_to_print[k]='/';
                        path_to_print[k+1]='\0';
                        strcat(path_to_print,namelist[i]->d_name);
                        // printf("%s\n",path_to_print);
                        if(namelist[i]->d_type== 4)   //directory
                        {
                            printf("\033[1;34m%s\033[1;0m\n", path_to_print);
                            count++;
                            if(S_IXUSR & mystruct.st_mode)
                            // printf("x");
                            {
                                strcpy(prev_dir,findcwd());
                                chdir(path_to_print);
                            }
                            else
                            {
                                printf("Missing permissions for task!\n");
                            }
                            
                        }
                        else    //files
                        {
                            printf("\033[1;32m%s\033[1;0m\n", path_to_print);
                            count++;
                            if(S_IRUSR & mystruct.st_mode)
                            // printf("x");
                            {
                                FILE* fptr=fopen(path_to_print,"r");
                                char c = fgetc(fptr);
                                while (c != EOF)
                                {
                                    printf ("%c", c);
                                    c = fgetc(fptr);
                                }
                                printf("\n");
                                fclose(fptr);
                                
                            }
                            else
                            {
                                printf("Missing permissions for task!\n");
                            }
                            
                        }
                        
                    }
                    if(namelist[i]->d_type== 4)
                    {
                        // printf("recursion here\n");
                        char newdir[4096];
                        strcpy(newdir,dir);
                        char slash[2];
                        slash[0]='/';
                        slash[1]='\0';
                        strcat(newdir,slash);
                        strcat(newdir,namelist[i]->d_name);
                        // printf("%s\n",newdir);
                        count+=actualseek(search,newdir,home_dir,e,d,f,givendir);
                    }
                }
                i++;
            }
        }
    
        else
        {
            count+=actualseek(search,dir,home_dir,0,0,0,dir);
        }
    }
    else if(e==1 && d==0 && f==1)
    {
        count=count_dir_and_files(search,dir,home_dir,e,d,f,givendir);
        if(count == 1)
        {
            struct dirent **namelist;
            int n;
            n = scandir(dir, &namelist, NULL, alphasort);
            if (n == -1) 
            {
                perror("scandir error\n");
                // exit(EXIT_FAILURE);
                return -1;
            }
            struct stat mystruct;
            int i=0;
            while(i!=n)
            {
                stat(namelist[i]->d_name,&mystruct);
                if(namelist[i]->d_name[0]!='.')
                {
                    char newname[4096];
                    int j=0;
                    while(!(namelist[i]->d_name[j]=='.'||namelist[i]->d_name[j]=='\0'))
                    {
                        newname[j]=namelist[i]->d_name[j];
                        j++;
                    }
                    newname[j]='\0';
                    if(strcmp(newname,search)==0)
                    {
                        char path_to_print[4096];
                        // char* cwd=findcwd();
                        // printf("%s",cwd);
                        int index=strlen(givendir);
                        path_to_print[0]='.';
                        int k=1;
                        while(dir[index]!='\0')
                        {
                            path_to_print[k++]=dir[index++];
                        }
                        path_to_print[k]='/';
                        path_to_print[k+1]='\0';
                        strcat(path_to_print,namelist[i]->d_name);
                        // printf("%s\n",path_to_print);
                        if(namelist[i]->d_type== 4)   //directory
                        {
                            // printf("\033[1;34m%s\033[1;0m\n", path_to_print);
                            // count++;
                            // if(S_IXUSR & mystruct.st_mode)
                            // // printf("x");
                            // {
                            //     strcpy(prev_dir,findcwd());
                            //     chdir(path_to_print);
                            // }
                            // else
                            // {
                            //     printf("Missing permissions for task!\n");
                            // }
                            
                        }
                        else    //files
                        {
                            printf("\033[1;32m%s\033[1;0m\n", path_to_print);
                            count++;
                            if(S_IRUSR & mystruct.st_mode)
                            // printf("x");
                            {
                                FILE* fptr=fopen(path_to_print,"r");
                                char c = fgetc(fptr);
                                while (c != EOF)
                                {
                                    printf ("%c", c);
                                    c = fgetc(fptr);
                                }
                                printf("\n");
                                fclose(fptr);
                                
                            }
                            else
                            {
                                printf("Missing permissions for task!\n");
                            }
                            
                        }
                        
                    }
                    if(namelist[i]->d_type== 4)
                    {
                        // printf("recursion here\n");
                        char newdir[4096];
                        strcpy(newdir,dir);
                        char slash[2];
                        slash[0]='/';
                        slash[1]='\0';
                        strcat(newdir,slash);
                        strcat(newdir,namelist[i]->d_name);
                        // printf("%s\n",newdir);
                        count+=actualseek(search,newdir,home_dir,e,d,f,givendir);
                    }
                }
                i++;
            }
        }
    
        else
        {
            count+=actualseek(search,dir,home_dir,0,0,0,dir);
        }
    }
    else if(e==1 && d==1 && f==0)
    {
        count=count_dir_and_files(search,dir,home_dir,e,d,f,givendir);
        if(count == 1)
        {
            struct dirent **namelist;
            int n;
            n = scandir(dir, &namelist, NULL, alphasort);
            if (n == -1) 
            {
                perror("scandir error\n");
                // exit(EXIT_FAILURE);
                return -1;
            }
            struct stat mystruct;
            int i=0;
            while(i!=n)
            {
                stat(namelist[i]->d_name,&mystruct);
                if(namelist[i]->d_name[0]!='.')
                {
                    char newname[4096];
                    int j=0;
                    while(!(namelist[i]->d_name[j]=='.'||namelist[i]->d_name[j]=='\0'))
                    {
                        newname[j]=namelist[i]->d_name[j];
                        j++;
                    }
                    newname[j]='\0';
                    if(strcmp(newname,search)==0)
                    {
                        char path_to_print[4096];
                        // char* cwd=findcwd();
                        // printf("%s",cwd);
                        int index=strlen(givendir);
                        path_to_print[0]='.';
                        int k=1;
                        while(dir[index]!='\0')
                        {
                            path_to_print[k++]=dir[index++];
                        }
                        path_to_print[k]='/';
                        path_to_print[k+1]='\0';
                        strcat(path_to_print,namelist[i]->d_name);
                        // printf("%s\n",path_to_print);
                        if(namelist[i]->d_type== 4)   //directory
                        {
                            printf("\033[1;34m%s\033[1;0m\n", path_to_print);
                            count++;
                            if(S_IXUSR & mystruct.st_mode)
                            // printf("x");
                            {
                                strcpy(prev_dir,findcwd());
                                chdir(path_to_print);
                            }
                            else
                            {
                                printf("Missing permissions for task!\n");
                            }
                            
                        }
                        else    //files
                        {
                            // printf("\033[1;32m%s\033[1;0m\n", path_to_print);
                            // count++;
                            // if(S_IRUSR & mystruct.st_mode)
                            // // printf("x");
                            // {
                            //     FILE* fptr=fopen(path_to_print,"r");
                            //     char c = fgetc(fptr);
                            //     while (c != EOF)
                            //     {
                            //         printf ("%c", c);
                            //         c = fgetc(fptr);
                            //     }
                            //     fclose(fptr);
                                
                            // }
                            // else
                            // {
                            //     printf("Missing permissions for task!\n");
                            // }
                            
                        }
                        
                    }
                    if(namelist[i]->d_type== 4)
                    {
                        // printf("recursion here\n");
                        char newdir[4096];
                        strcpy(newdir,dir);
                        char slash[2];
                        slash[0]='/';
                        slash[1]='\0';
                        strcat(newdir,slash);
                        strcat(newdir,namelist[i]->d_name);
                        // printf("%s\n",newdir);
                        count+=actualseek(search,newdir,home_dir,e,d,f,givendir);
                    }
                }
                i++;
            }
        }
    
        else
        {
            actualseek(search,dir,home_dir,0,0,0,dir);
        }
    }
    return count;
}

void seek(char* input, char* home_dir)
{
    if(strcmp("seek",input)==0)
    {
        printf("incomplete command!!\n");
        return;
    }
    // printf("%s",input);
    if(input[5]=='-')
    {
        int d=0,f=0,e=0;
        //flags to be handled
        int j=5;
        for(int i=5;i<strlen(input);i++)
        {
            if(input[i]=='-')
            {
                i++;
                while(i<strlen(input)&&input[i]!=' ')
                {
                    if(input[i]=='d')
                        d=1;
                    else if(input[i]=='e')
                        e=1;
                    else if(input[i]=='f')
                        f=1;
                    else
                    {
                        printf("Invalid flags!\n");
                        return;
                    }
                    i++;
                }
                j=i;
            }
        }
        char mytoken[4096];
        char mysearch[4096];
        char mydir[4096];
        j++;
        int k=0;
        while(input[j]!='\0')
        {
            mytoken[k++]=input[j++];
        }
        mytoken[k]='\0';
        // printf("%s\n",mytoken);
        char* search=strtok(mytoken," ");
        strcpy(mysearch,search);
        // printf("%s ",search);
        char* dir=strtok(NULL," ");
        if(dir==NULL)
        {
            strcpy(mydir,findcwd());
        }
        else
        {
            if(strcmp("-",dir)==0)
            {
                if(prev_dir[0]=='\0')
                {
                    printf("old pwd not set!!\n");
                }
                else
                {
                    strcpy(mydir,prev_dir);
                }
            }
            else if(strcmp("~",dir)==0)
            {
                strcpy(mydir,home_dir);
            }
            else
            {
                strcpy(mydir,dir);
            }
        }
        // printf("%s\n",mydir);
        int count=actualseek(mysearch,mydir,home_dir,e,d,f,mydir);
        if(count==0)
        {
            printf("No match found!\n");
        }
    }
    else
    {
        char mytoken[4096];
        char mysearch[4096];
        char mydir[4096];
        char* token=strtok(input," ");
        strcpy(mytoken,token);
        char* search=strtok(NULL," ");
        strcpy(mysearch,search);
        // printf("%s ",search);
        char* dir=strtok(NULL," ");
        if(dir==NULL)
        {
            strcpy(mydir,findcwd());
        }
        else
        {
            if(strcmp("-",dir)==0)
            {
                if(prev_dir[0]=='\0')
                {
                    printf("old pwd not set!!\n");
                }
                else
                {
                    strcpy(mydir,prev_dir);
                }
            }
            else if(strcmp("~",dir)==0)
            {
                strcpy(mydir,home_dir);
            }
            else
            {
                strcpy(mydir,dir);
            }
        }
        // printf("%s\n",mydir);
        int count=actualseek(mysearch,mydir,home_dir,0,0,0,mydir);
        if(count==0)
        {
            printf("No match found!\n");
        }
    }
}