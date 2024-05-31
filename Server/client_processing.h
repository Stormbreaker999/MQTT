#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>

#include<netinet/in.h>



int processclients(int serverfd)
{
    int MAX_CLIENTS=10;
    struct client_list *clist=NULL;
    
    int count=0;
    while(1){
    	if(count<MAX_CLIENTS){
    	    struct sockaddr_in cliaddr;
    	    socklen_t clilen=sizeof(cliaddr);
    	    int newfd=accept(serverfd, (struct sockaddr *) &cliaddr, &clilen);
    	    if(newfd<0){
    	        printf("Error on accepting connection");
    	        continue;
    	    }
    	    else{
    	        //Fork to be implemented here
    	        
    	        clist=addnewclient(clist, newfd);
    	        
    	        int cpid=fork();
    	        if(cpid==0){
    	            message_handler(newfd);
    	            clist=removeclient(clist, newfd);
    	            exit(0);
    	        }
    	        else{
    	            continue;
    	        }
    	    }
    	}
    	else{
    	    printf("Connection slots full");
    	}
    
    }
}


    
    
    
    
    
    
    
