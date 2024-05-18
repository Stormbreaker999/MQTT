#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<netdb.h>

#include "connectserver.h"
#include "messageclient.h"

int main(int argc, char *argv[]){
    if(argc<3){
        printf("Port number or server address not specified\n");
        exit(0);
    }
    int myfd=connect_to_server(argv[1], atoi(argv[2]));
    message_processing(myfd);
    
    return 0;
}
