#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>

#include<netinet/in.h>
#include "data_handler.h"
#include "socket.h"
#include "message.h"


#include "client_processing.h"



//Maximum number of clients that can simultaneously connect to the broker
#define MAX_CLIENTS 10

int main(int argc, char *argv[]){
    if(argc<2){
        printf("Port number required in the command");
        exit(0);
    }
    int sockfd=createlistener(atoi(argv[1]));
    //if(sockfd) printf("Creation and binding succeeded");
    
    listen(sockfd, MAX_CLIENTS);
    processclients(sockfd);
    return 0;
}
