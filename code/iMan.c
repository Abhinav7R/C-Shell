#include "headers.h"

extern char prev_dir[4096];

void iMan(char *input)
{
    // printf("%s\n",input);
    char command[4096];
    int i = 5;
    while (!(input[i] == ' ' || input[i] == '\0'))
    {
        // printf("%d\n",i);
        command[i - 5] = input[i];
        i++;
    }
    command[i - 5] = '\0';
    // printf("...%s\n",command);

    struct hostent *host;
    struct sockaddr_in server_addr;
    int sockfd;

    // DNS resolution for man.he.net
    host = gethostbyname("man.he.net");
    if (host == NULL)
    {
        perror("DNS resolution failed");
        return;
    }

    //socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1)
    {
        perror("Socket creation failed");
        return;
    }

    // Initialize server_addr
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(80);
    server_addr.sin_addr = *((struct in_addr *)host->h_addr);

    // Connect to server
    if (connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1)
    {
        perror("Connection to server failed");
        close(sockfd);
        return;
    }

    // Send the HTTP GET request
    char request[4096 * 3];

    snprintf(request, sizeof(request), "GET /?topic=%s&section=all HTTP/1.1\r\nHost: man.he.net\r\n\r\n", command);
    // printf("%s\n",request);
    if (send(sockfd, request, strlen(request), 0) == -1)
    {
        perror("HTTP GET request failed");
        close(sockfd);
        return;
    }

    // Receive and print the response
    char response[100000] = {0};
    int bytes_received;
    int flag = 0;
    char *ptrtopre;
    while ((bytes_received = recv(sockfd, response, sizeof(response) - 1, 0)) > 0)
    {
        response[bytes_received] = '\0';
        
        ptrtopre = strstr(response, "<PRE>");
        if (ptrtopre != NULL)
            ptrtopre = ptrtopre + 5;
        else
            ptrtopre = response;

        char *ptrtoendpre = strstr(response, "</PRE>");
        if (ptrtoendpre == NULL)
        {
            while (ptrtopre[0] != '\0')
            {
                if(ptrtopre[0]=='<')
                    flag=1;
                if(flag==0)        
                    printf("%c", ptrtopre[0]);
                if(ptrtopre[0]=='>')
                    flag=0;
                ptrtopre += 1;
            }
        }
        else
            while (ptrtopre != ptrtoendpre)
            {
                if(ptrtopre[0]=='<')
                    flag=1;
                if(flag==0)        
                    printf("%c", ptrtopre[0]);
                if(ptrtopre[0]=='>')
                    flag=0;    
                ptrtopre += 1;
            }
    }
    printf("\n");

    if (bytes_received == -1)
    {
        perror("Error receiving response");
    }

    // Close the socket
    close(sockfd);
}