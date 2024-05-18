#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>

#include<netinet/in.h>

struct client_list{
    int cli_fd;
    struct client_list* next;
};


//struct client_list *addnewclient(struct client_list *, int);
//struct client_list *removeclient(struct client_list *, int);

struct client_list *addnewclient(struct client_list *head, int clifd){
    struct client_list *newclient=malloc(sizeof(struct client_list));
    newclient->cli_fd=clifd;
    newclient->next=head;
    return newclient;
}

struct client_list *removeclient(struct client_list *clist, int clifd){
    if(!clist){
        printf("Error occurred in removing client\n");
        printf("Exitting");
        exit(0);
    }
    if(clist->cli_fd==clifd){
    	struct client_list *temp=clist->next;
    	free(clist);
        return temp;
    }
    else{
        struct client_list *ptr=clist;
        while(ptr && ptr->next && ptr->next->cli_fd!=clifd) ptr=ptr->next;
        if(!ptr){
            printf("Error occurred in removing client\n");
            printf("Exitting");
            exit(0);
        }
        else{
            struct client_list *temp=ptr->next;
            ptr->next=ptr->next->next;
            free(temp);
        }
    }
    return clist;
}

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


    
    
    
    
    
    
    
