int connect_to_server(char *IP, int port){
   int mysockfd, serversockfd;
   struct hostent* server;
   
   struct sockaddr_in serv_addr;
   socklen_t clilen;
   mysockfd=socket(AF_INET, SOCK_STREAM, 0);
   if(mysockfd==-1){
      printf("Error opening socket");
      exit(0);
   }
   
   server=gethostbyname(IP);
   if(server==NULL){
      fprintf(stderr, "Error! No such host");
      exit(0);
   }
   bzero((char *)&serv_addr, sizeof(serv_addr));
   serv_addr.sin_family=AF_INET;
   bcopy((char *)server->h_addr, (char *) &serv_addr.sin_addr.s_addr, server->h_length);
   serv_addr.sin_port=htons(port);
   if(connect(mysockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr))<0){
       printf("Error Connecting");
       exit(0);
   }
   else printf("Connected Successfully\n");
   return mysockfd;
}
