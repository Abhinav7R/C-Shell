#include "headers.h"

extern char prev_dir[4096];

void pastevents(char* input, Queue head, char* home_dir)
{
    // printf("entered pastevents!\n");
    // printf("%s\n",input);
    if(strcmp(input,"pastevents\0")==0)
    {
        char file[4096];
        strcpy(file,home_dir);
        char past[100]="/pastevents\0";
        strcat(file,past);
        FILE* fp1=fopen(file,"r");
        if(fp1==NULL)
        {
            printf("file can't be opened!!\n");
            return;
        }
        char to_be_printed[4096];
        char ch;
        int i=0;
        while((ch=fgetc(fp1))!=EOF)
        {
            to_be_printed[i++]=ch;
        }
        to_be_printed[i]='\0';
        printf("%s",to_be_printed);
        fclose(fp1);
    }

    else if(strcmp(input,"pastevents purge\0")==0)
    {
        char file[4096];
        strcpy(file,home_dir);
        char past[100]="/pastevents\0";
        strcat(file,past);
        FILE* fp1=fopen(file,"w");
        if(fp1==NULL)
        {
            printf("file can't be opened!!\n");
            return;
        }
        fclose(fp1);

    }

    else if(strncmp(input,"pastevents execute ",19)==0)
    {
        // printf("%d\n",length);
        int i=0;
        while(!(input[i]<='9' && input[i]>='1'))
        {
            i++;
        }
        char number[10];        //number as a string
        int index=0;
        while(input[i]!='\0')
        {
            number[index++]=input[i++];
        }
        number[index]='\0';
        // printf("%s",number);
        int num=convert_to_int(number);
        // printf("%d\n",num);

        char file[4096];
        strcpy(file,home_dir);
        char past[100]="/pastevents\0";
        strcat(file,past);
        // printf("%s",file);

        FILE* fp1=fopen(file,"r");
        if(fp1==NULL)
        {
            printf("file can't be opened!!\n");
            return;
        }
        fseek(fp1,0,SEEK_END);
        int size=ftell(fp1);
        fseek(fp1,0,SEEK_SET);

        if(size==0)
        {
            printf("no pastevents!!\n");
            fclose(fp1);
            return;
        }
        int lines=0;
        char ch;
        while((ch=fgetc(fp1))!=EOF) 
        {
            if(ch=='\n')
                lines++;
        }
        
        fseek(fp1,0,SEEK_SET);

        if(lines<num)
        {
            printf("%d number of events havent taken place!!\n",num);
            fclose(fp1);
            return;
        }
        
        int line_from_top=lines-num+1;
        int no_of_new_line_chars=0;
        char command_to_execute[4096];
        while(no_of_new_line_chars!=line_from_top-1)
        {
            ch=fgetc(fp1);
            if(ch=='\n')
            {
                no_of_new_line_chars++;
            }
        }
        fgets(command_to_execute,4096,fp1);
        // printf("%s",command_to_execute);
        fclose(fp1);
        execute(command_to_execute,head,home_dir);

    }

}

void store_command(char* command, char* home_dir)
{
    if(strcmp(command,"pastevents\0")==0)
    {
        return;
    }
    if(strcmp(command,"pastevents purge\0")==0)
    {
        return;
    }
    if(strncmp(command,"pastevents execute ",19)==0)
    {
        return;
    }
    char new[2];        //check if enter was pressed on shell
    new[0]='\0';
    new[1]='\0';

    char file[4096];
    strcpy(file,home_dir);
    char past[100]="/pastevents\0";
    strcat(file,past);
    // printf("%s",file);

    int lines=0;
    FILE* fp1=fopen(file,"r");
    if(fp1==NULL)
    {
        printf("file can't be opened!!\n");
        return;
    }
    // printf("opened\n");
    char ch;
    fseek(fp1,0,SEEK_END);
    int size=ftell(fp1);
    fseek(fp1,0,SEEK_SET);
    char last_line[4096];
    int fifteen_flag=0;
    char new_contents[4096];
    if(size!=0)
    {
        while((ch=fgetc(fp1))!=EOF) 
        {
            if(ch=='\n')
                lines++;
        }
        
        fseek(fp1,0,SEEK_SET);
        
        // printf("%d\n",lines);
        if(lines!=0)
        {
            int newlinechars=0;
            while(newlinechars!=(lines-1))
            {
                ch=fgetc(fp1);
                if(ch=='\n')
                    newlinechars++;
            }
            
            fgets(last_line,4096,fp1);
            // printf("last line %s",last_line);
        }
        fseek(fp1,0,SEEK_SET);
        if(lines==15)
        {
            // printf("here!!\n");
            int i=0;
            
            while(1) 
            {
                ch=fgetc(fp1);
                if(ch=='\n')
                {
                    break;
                }
            }
            while((ch=fgetc(fp1))!=EOF)
            {
                new_contents[i++]=ch;
            }
            new_contents[i]='\0';
            // printf("%s",new_contents);
            // fseek(fp1,0,SEEK_SET);
            fifteen_flag=1;
            fclose(fp1);
            // fputs(new_contents,fp1);
        }
    }
    if(fifteen_flag==1)
    {
        //check for last command is same 
        char last_line_to_compare[4096];
        int i=0;
        while(last_line[i]!='\n')
        {
            last_line_to_compare[i]=last_line[i];
            i++;
        }
        last_line_to_compare[i]='\0';
        if((strcmp(command,new)!=0)&&strcmp(last_line_to_compare,command)!=0)
        {
            FILE* fp2=fopen(file,"w");
            fputs(new_contents,fp2);
            fclose(fp2);
        }
    }
    else
        fclose(fp1);

    FILE* fp=fopen(file,"a");
    if(fp==NULL)
    {
        printf("file can't be opened!!\n");
        return;
    }
    
    // printf("%s",command);
    if(strcmp(command,new)!=0)              //check if its just an enter
    {
        // printf("last line: %s and command: %sokay\n",last_line,command);
        char last_line_to_compare[4096];
        int i=0;
        while(last_line[i]!='\n')
        {
            last_line_to_compare[i]=last_line[i];
            i++;
        }
        last_line_to_compare[i]='\0';
        if(strcmp(last_line_to_compare,command)!=0)
        {
            fputs(command,fp);
            fputc('\n',fp);
        }
    }
    fclose(fp);
}