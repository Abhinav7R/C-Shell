#include "headers.h"

extern char prev_dir[4096];

int convert_to_int(char* pidstring)
{
    int pid=0;
    int length=strlen(pidstring);
    for(int i=0;i<length;i++)
    {
        pid=pid*10+(pidstring[i]-'0');
    }
    return pid;
}

void proclore(char* input)
{
    int pid=0;
    // printf("entered proclore\n");
    if(input[8]=='\0')
    {
        //process is my shell
        // printf("%d\n",getpid());
        pid=getpid();
    }
    else
    {
        char pidstring[100];
        int i=9;
        while(input[i]!='\0')
        {
            pidstring[i-9]=input[i];
            i++;
        }
        pidstring[i-9]='\0';
        // printf("%s\n",pidstring);
        pid=convert_to_int(pidstring);
        // printf("%d\n",pid);
    }

    //got pid in int format
    printf("pid : %d\n",pid);
    char filename[4096];
    // strcpy(filename,"/proc/");
    sprintf(filename,"/proc/%d/stat",pid);
    // printf("%s",filename);
    FILE* fp=fopen(filename,"r");
    if(fp==NULL)
    {
        printf("error in opening file!! Invalid pid!!\n");
        return;
    }
    char c = fgetc(fp);
    while (c != ')')
    {
        // printf ("%c", c);
        c = fgetc(fp);
    }
    c = fgetc(fp);
    c = fgetc(fp);
    char status[10];
    while (c != ' ')
    {
        sprintf(status,"%c",c);
        c = fgetc(fp);
        // printf ("%c", c);
    }
    // printf("\n");
    fclose(fp);
    printf("Process Status : %s\n",status);

    printf("Process Group : %d\n",getpgid(pid));

    char secondfile[4096];
    sprintf(secondfile,"/proc/%d/status",pid);
    FILE* fp2=fopen(secondfile,"r");
    if(fp2==NULL)
    {
        printf("error in opening file!! Invalid pid!!\n");
        return;
    }
    char line[4096];
    fgets(line,100,fp2);
    int flag=0;
    while(strncmp("VmSize",line,6)!=0)
    {
        if(fgets(line,100,fp2)==NULL)
        {
            flag=1;
            break;
        }
    }
    if(flag!=1)
    {
        char memory[4096];
        int l=0;
        while(!(line[l]>=48 && line[l]<=57))        //line[l] belongs to 0-9
        {
            l++;
        }
        strcpy(memory,line+l);
        printf("Virtual memory : %s",memory);
    }
    else
    {
        printf("Vitual memory not found!\n");
    }
    fclose(fp2);

    char thirdfile[4096];
    sprintf(thirdfile,"/proc/%d/exe",pid);
    // FILE* fp3=fopen(thirdfile,"r");
    // if(fp3==NULL)
    // {
    //     printf("error in opening file!! Invalid pid!!\n");
    //     return;
    // }
    char buffer[4096];
    buffer[0]='\0';
    readlink(thirdfile,buffer,100);
    if(buffer[0]!='\0')
    {
        printf("%s\n",buffer);
    }
    else
    {
        printf("exe path not found!!\n");
    }

}