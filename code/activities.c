#include "headers.h"

extern char prev_dir[4096];

int comparator(const void* a, const void* b) {
    return strcmp(*(const char**)a, *(const char**)b);
}

void activities(Queue head)
{
    // printf("entered activities\n");
    int number_of_processes=head->val;
    Queue temp=head->next;

    char** processes=(char**)malloc(sizeof(char*)*number_of_processes);
    for(int i=0;i<number_of_processes;i++)
    {
        processes[i]=(char*)malloc(sizeof(char)*4096);
    }
    int i=0;
    int num=number_of_processes;
    while(number_of_processes--)
    {
        int pid=temp->val;
        //add to processes
        char my_string[4096];
        sprintf(my_string,"%d : ",pid);
        strcat(my_string,temp->name);
        strcat(my_string," - ");
        // printf("%d : ",pid);
        // printf("%s - ",temp->name);
        //code same as proclore
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
        if(strcmp("T",status)==0)
        {
            strcat(my_string,"Stopped\n");
        }
        else
        {
            strcat(my_string,"Running\n");
        }
        // printf("%s\n",status);
        // printf("%s",my_string);
        strcpy(processes[i],my_string);
        temp=temp->next;
        i++;
    }
    qsort(processes,num,sizeof(char*),comparator);

    for(int i=0;i<num;i++)
    {
        printf("%s",processes[i]);
    }

}