void error(const char *msg){
   perror(msg);
   exit(1);
}

int createlistener(int port){
    int sockfd;
    struct sockaddr_in servaddr;
    sockfd=socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd==-1){
    	printf("Error in creating socket\n");
    }
    bzero((char *) &servaddr, sizeof(servaddr));
    servaddr.sin_family=AF_INET;
    servaddr.sin_addr.s_addr=INADDR_ANY;
    servaddr.sin_port=htons(port);
    if(bind(sockfd, (struct sockaddr*) &servaddr, sizeof(servaddr))<0){
        printf("Binding to socket failed\n");
    }
    return sockfd;
}
        
    
