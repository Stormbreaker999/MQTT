#include<stdbool.h>
#include<stdio.h>
#include<time.h>
#define MAX_PACKET_SIZE 2048

int connectmsg(int);
void handle_publisher(int);
void handle_consumer(int);
void disconnect(int , char *);

void message_processing(int sockfd){
    char buffer[MAX_PACKET_SIZE];
    bool isPublisher;
    char ans;
    printf("Are you a publisher or subscriber (p/s): ");
    scanf("%c", &ans);
    if(ans=='p') isPublisher=true;
    else if(ans=='s') isPublisher=false;
    else{
        printf("Invalid Response\n");
        return;
    }
    int con=connectmsg(sockfd);
    if(con<-1){
        printf("Invalid Acknowledgement\nTrying again...");
        message_processing(sockfd);
    }
    else if(con==1){
    	//To be handled later
        printf("Piggybacking Message");
    }
    else printf("Pure Acknowledgement Received\n");
   
    
    if(isPublisher){
    	handle_publisher(sockfd);
        
    }    
    else{
        handle_consumer(sockfd);
    }
        
}


int connectmsg(int sockfd){
    char buffer[MAX_PACKET_SIZE];
    bzero(buffer, sizeof(buffer));
    buffer[0]=16;
    buffer[1]='\0';
    int n=send(sockfd, buffer, strlen(buffer) ,0);
    if(n<0){
        printf("Connection request failed\n");
        exit(0);
    }
    n=recv(sockfd, buffer, sizeof(buffer), 0);
    if(n<0){
        printf("Error in receiving acknowledgement\n");
        exit(0);
    }
    else{
        if(buffer[0]==8) return 0;
        if(buffer[0]==24) return 1;
        else return -1;
    }
}

void handle_publisher(int sockfd){
    char buffer[MAX_PACKET_SIZE];
    while(1){
        char ans='y';
        
        printf("Want to publish any data (y/n): ");
        getchar();
        scanf("%c", &ans);
        if(ans=='n') break;
        char TOPIC[8];
        printf("Enter topic name(<=7): ");
        scanf("%s", TOPIC);
        getchar();
        
        char MSG[2025];
        printf("Enter the message:(<=2024 characters) ");
        scanf("%[^\n]s", MSG);
        getchar();
        printf("%s %s\n", TOPIC, MSG);
        bzero(buffer, MAX_PACKET_SIZE);
          
        int topic_length=strlen(TOPIC);
        topic_length=topic_length<<4;
        
        int msg_length=strlen(MSG);
        int second_byte=topic_length+(msg_length>>8);
        int third_byte=msg_length-((msg_length>>8)<<8);
        
        //Publish message 00100000 = 32
        buffer[0]=32;
        buffer[1]=second_byte;
        buffer[2]=third_byte;
        buffer[3]='\0';
        strcat(buffer, TOPIC);
        strcat(buffer, MSG);
        
        int n=send(sockfd, buffer, strlen(buffer), 0);
        if(n) printf("Publish Message Sent successfully\n");
        bzero(buffer, MAX_PACKET_SIZE);
        n=recv(sockfd, buffer, MAX_PACKET_SIZE, 0);
        
        if(buffer[0]==40){
            printf("Publish Acknowledgement Received\n");
        }
    }
    printf("Disconnect from the server (y/n) : ");
    char ans='y';   
    scanf("%c", &ans);
    if(ans=='y'){
    	disconnect(sockfd, buffer);
    	
    	
    }
    else if(ans=='n'){
        handle_consumer(sockfd);
    }
    else{
        printf("Invalid Response\nExitting!");
        disconnect(sockfd, buffer);
    }
}

void handle_consumer(int sockfd){
    char buffer[MAX_PACKET_SIZE];
    getchar();
    char ans;
    printf("Want to subscribe any data (y/n): ");
        
    scanf("%c", &ans);
    getchar();
    char TOPIC[8];
    printf("Enter topic name(<=7): ");
    scanf("%s", TOPIC);
    getchar();
    char prev[2025]="";
    while(1){ 
        //Subscribe message 00110000 48
        bzero(buffer, sizeof(buffer));
        buffer[0]=48;
        int topic_length=strlen(TOPIC);
        buffer[1]=topic_length<<4;
        int i=0;
        for(;i<topic_length;i++){
            buffer[2+i]=TOPIC[i];
        }
        buffer[2+i]='\0';
        
        int n=send(sockfd, buffer, strlen(buffer),0);
        //if(n){
        //   printf("Subscribe Message sent successfully\n");
        //}
        
        bzero(buffer,sizeof(buffer));
        n=recv(sockfd, buffer, sizeof(buffer),0);
        
        if(n){
            if(buffer[0]==56){
                printf("Subscribe Acknowledgement Received\n");
              
            }
            else if(buffer[0]==60){
            	
                printf("Piggybacking Acknowledgement Received\n");
                int topic_length=buffer[1]>>4;
              
             	char topic[8];
             	int i=0;
             	while(i<topic_length){
                    topic[i]=buffer[i+3];
                    i++;
             	}
             	topic[i]='\0';
             	char *msg=buffer+3+i;
             	if(strcmp(prev,msg)==0){
             	    printf("No new event occurred\n");
             	    time_t start=time(NULL); 
             	    while(time(NULL)-start<=3);
             	    char dis;
            	    printf("Want to disconnect(y/n): ");
            	    scanf("%c", &dis);
            	    getchar();
            	    if(dis=='y') break;
            	    printf("Waiting for messages->\n");
            	    continue;
            	}
            
             	strcpy(prev,msg);
             	printf("Topic length =  %d\n", topic_length);
             
             	printf("Topic - %s\n", topic);
             	printf("Message - %s\n", msg);
             	
             	
            }
        }
        
            char dis;
            printf("Want to disconnect(y/n): ");
            scanf("%c", &dis);
            getchar();
            if(dis=='y') break;
            
            printf("Waiting for messages->\n");
            
        
    }
    
    disconnect(sockfd, buffer);
   
}
        
        
void disconnect(int sockfd, char *buffer){
    //Disconnect Message 01000000 = 64
    bzero(buffer, sizeof(buffer));
    buffer[0]=64;
    buffer[1]='\0';
    int n=send(sockfd,buffer, strlen(buffer),0);
    //Receiving Disconnect Acknowledgement
    bzero(buffer, sizeof(buffer));
    n=recv(sockfd,buffer, sizeof(buffer),0);
    if(buffer[0]==72){
        printf("Received Disconnect Acknowledgement\n");
        
    }
    else{
        printf("Error in disconnection\nExitting");
        
    }
}
       
     
        
