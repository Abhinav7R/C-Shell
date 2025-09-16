#include "headers.h"

extern char prev_dir[4096];

void die(const char *s)
{
    perror(s);
    exit(1);
}

struct termios orig_termios;

void enableRawMode()
{
    if (tcgetattr(STDIN_FILENO, &orig_termios) == -1)
        die("tcgetattr");
    atexit(disableRawMode);
    struct termios raw = orig_termios;
    // raw.c_lflag &= ~(ICANON | ECHO);
    raw.c_cflag |= (CLOCAL | CREAD);
    raw.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);
    raw.c_oflag &= ~OPOST;
    raw.c_cc[VMIN] = 0;
    raw.c_cc[VTIME] = 1;
    if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw) == -1)
        die("tcsetattr");
}

void disableRawMode()
{
    if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios) == -1)
        die("tcsetattr");
}

void neonate(char *input)
{
    // printf("^%s^\n",input);
    enableRawMode();
    // printf("neonate\n");
    int i = 11;
    char timestring[100]={0};
    while (input[i] != '\0')
    {
        timestring[i - 11] = input[i];
        i++;
    }
    timestring[i - 11] = '\0';

    int my_time = convert_to_int(timestring);
    // printf("%d\n",my_time);
    // int child_pid=fork();
    // printf("%d\r\n",child_pid);
    // if(child_pid<0)
    // {
    //     printf("error in forking\n");
    //     return;
    // }
    // if(child_pid==0)
    // {
    
    int input_copyy=dup(STDIN_FILENO);
    while (1)
    {
        char c[2]={0};
        read(STDIN_FILENO, c, sizeof(c));
        printf("%c\n",c[0]);
        if (c[0] == 'x')
        {
            // printf("here\r\n");
            // kill(child_pid, SIGKILL);
            break;
        }
        // printf("child\r\n");
        // child
        FILE *fp = fopen("/proc/loadavg", "r");
        if (fp == NULL)
        {
            printf("error in openeing file\n");
            disableRawMode();
            dup2(input_copyy,STDIN_FILENO);    
            return;
        }

        char loadavg[1024];
        fread(loadavg, 1, 1024, fp);
        fclose(fp);
        // printf("%s\r\n",loadavg);
        int spaces = 0;
        int ii = 0;
        while (spaces != 4)
        {
            if (loadavg[ii] == ' ')
            {
                spaces++;
            }
            ii++;
        }
        char latest_pid[4096];
        int j = 0;
        while (loadavg[ii] != '\0')
        {
            latest_pid[j] = loadavg[ii];
            ii++;
            j++;
        }
        latest_pid[j] = '\0';
        // int my_latest_pid=convert_to_int(latest_pid);
        printf("%s\r\n", latest_pid);
        // printf("%d\r\n",my_latest_pid);
        // printf("hellio\r\n");
        sleep(my_time);
    }

    // }
    // else if(child_pid>0)
    // {
    //     // printf("parent\r\n");
    //     //parent
    //     char c[2];
    //     while(1)
    //     {
    //         // printf("i am here\r\n");
    //         read(STDIN_FILENO, c, sizeof(c));
    //         if(c[0]=='x')
    //         {
    //             // printf("here\r\n");
    //             kill(child_pid,SIGKILL);
    //             break;
    //         }
    //     }
    //     disableRawMode();
    //     return;
    // }

    disableRawMode();
    dup2(input_copyy,STDIN_FILENO);
}