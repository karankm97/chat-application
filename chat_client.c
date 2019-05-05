#include<sys/socket.h>
#include<stdio.h>
#include<string.h>
#include<netdb.h>
#include<stdlib.h>

int main()
{
    char buf[100];
    int k;
    int sock_desc;
    struct sockaddr_in client;
    memset(&client,0,sizeof(client));
    sock_desc=socket(AF_INET,SOCK_STREAM,0);

    if(sock_desc==-1)
    {
        printf("Socket creation error");
        exit(1);
    }

    client.sin_family=AF_INET;
	client.sin_addr.s_addr=inet_addr("127.0.0.1");
	client.sin_port=3002;

    k=connect(sock_desc,(struct sockaddr*)&client,sizeof(client));
    if(k==-1)
    {
        printf("Error in connecting to server");
        exit(1);
    }

    while(1)
    {
        printf("\n Data to be sent to server: ");
        fgets(buf,100,stdin);
        if(strncmp(buf,"end",3)==0)
            break;

        k=send(sock_desc,buf,100,0);
        if(k==-1)
        {
            printf("Sending error");
            exit(1);
        }

        k=recv(sock_desc,buf,100,0);
        if(k==-1)
        {
            printf("Error in receiving");
            exit(1);
        }

        printf("Message received from server : %s",buf);
    }
    close(sock_desc);
    exit(0);
    return 0;
}
