#include "headers.h"

extern char prev_dir[4096];

int execute(char* input, Queue head, char* cwd)
{

        // char* command_to_store=(char*)malloc(sizeof(char)*4096);
        // command_to_store=make_good(input);
        // store_command(command_to_store, cwd);
        // char* good_input=store_input(input);
        char delimiters[]=";\n";
        char* saveptr1;
        char* token=strtok_r(input,delimiters,&saveptr1);
        int flag=0;
        while(token!=NULL)
        {
            // printf("%s\n",token);
            // char* saveptr2;
            // char delimit2[]="&";
            // char* token2=strtok_r(token,delimit2,&saveptr2);
            // while(token2!=NULL)
            // {
                // printf("%s\n",token2);
                char* good_token=check_correctness(token);
                if(good_token==NULL)
                {
                    printf("command invalid!\n");
                    flag=1;
                    break;
                }
                // printf("%s\n",good_token);
                char** commands=(char**)malloc(sizeof(char*)*10);
                for(int h=0;h<10;h++)
                {
                    commands[h]=(char*)malloc(sizeof(char)*100);
                }
                int h=0;
                int command_index=0;
                int ii=0;
                while(good_token[h]!='\0')
                {
                    commands[command_index][ii++]=good_token[h];
                    if(good_token[h]=='&')
                    {
                        commands[command_index][ii]='\0';
                        command_index++;
                        ii=0;
                    }
                    h++;
                }
                commands[command_index][ii]='\0';
                int p=0;
                while(p<=command_index)
                {
                    char* good_token2=check_correctness(commands[p]);

                    int task=which_task(good_token2);
                    if((contains_io_pipe(good_token2))==1)
                        iopipe(good_token2,head);
                    else
                    {    
                        switch (task)
                        {
                            case 3:
                                warp(good_token2,cwd);
                                break;

                            case 4:
                                peek(good_token2,cwd);
                                break;    

                            case 8:
                                seek(good_token2,cwd);
                                break;

                            case 7:
                                proclore(good_token2);
                                break;  

                            case 6:
                                pastevents(good_token2, head, cwd);
                                break;  

                            case 12:
                                activities(head);
                                break;  

                            case 13:
                                ping(good_token2);
                                break; 

                            case 14:
                                bg(good_token2);
                                break;

                            case 17:
                                fg(good_token2);
                                break;  

                            case 16:
                                iMan(good_token2);
                                break;  

                            case 15:
                                neonate(good_token2);
                                break;                        

                            case 0:
                                // printf("%s is not a valid command!\n",good_token2);
                                // if((contains_io_pipe(good_token2))==0)
                                fgbg(good_token2, head);
                                // else
                                //     iopipe(good_token2,head);    
                                break;

                            default:
                                break;
                        }
                    }
                    p++;
                }
                // token2=strtok_r(NULL,delimit2,&saveptr2);
            // }
            token=strtok_r(NULL,delimiters,&saveptr1);
        }

        return flag;
}