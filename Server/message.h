#include<string.h>



void sendack(int);
int handleclient(int);




void message_handler(int clifd){
    char buffer[2048];
    
    bzero(buffer, sizeof(buffer));
    int n=recv(clifd, buffer, sizeof(buffer),0);
    if(n>=0){
        if(buffer[0]==16) sendack(clifd);
        else{
            send(clifd, "Invalid Request", 15, 0);
            exit(0);
        }
    }
    else{
        send(clifd, "Connect again", 13, 0);
        message_handler(clifd);
    }
    
    
    int con=1;
    while(con==1){
    	
        con=handleclient(clifd);    
    }
    if(con==2){
        //termination
        printf("Disconnected from client\n");
        exit(0);
    }
    else{
        printf("Invalid Request\nExitting\n");
        exit(0);
    }
    
    
}


void sendack(int clifd){
    char msg[2];
    msg[0]=8;
    msg[1]='\0';
    int n=send(clifd, msg, 2, 0);
    if(n) printf("Acknowledgement Sent Successfully\n");
    
}

int handleclient(int clifd){
    char buffer[2048];
    bzero(buffer, sizeof(buffer));
    int n=recv(clifd, buffer, sizeof(buffer), 0);
    
    if(n){
         if(buffer[0]==32){
             //Publish Message
             //First Byte = Topic Length and Message Length
             int topic_length=buffer[1]>>4;
             char topic[8];
             int i=0;
             while(i<topic_length){
                 topic[i]=buffer[i+3];
                 i++;
             }
             topic[i]='\0';
             char *msg=buffer+3+i;
             //Saving to file
             write_to_file(topic, msg);
             printf("Topic length =  %d\n", topic_length);
             
             printf("Topic - %s\n", topic);
             printf("Message - %s\n", msg);
             
             
             //Send Publish Acknowledgement
             bzero(buffer, sizeof(buffer));
             buffer[0]=40;
             buffer[1]='\0';
             n=send(clifd, buffer, strlen(buffer), 0);
             if(n) return 1;
             
         }
         else if(buffer[0]==48){
             //Subscribe message
             
             int topic_length=buffer[1]>>4;
             char topic[8];
             int i=0;
             while(i<topic_length){
                 topic[i]=buffer[i+2];
                 i++;
             }
             topic[i]='\0';
             printf("%s\n", topic);
             //Reading from file
             char msg[2025];
             int len=read_from_file(topic, msg);
             
             
             bzero(buffer, sizeof(buffer));
             //Piggybacking 00111100 = 60
             if(len){
             	printf("%d", len);
             	msg[len-2]='\0';
             	len=strlen(msg);
             	buffer[0]=60;
             	buffer[1]=topic_length<<4;
             	buffer[1]+=len>>8;
             	buffer[2]=len^((len<<8)-1);
             	
             	int i=0;
             	for(;i<topic_length;i++){
             	    buffer[3+i]=topic[i];
             	}
             	i=0;
             	for(;i<len;i++){
             	    buffer[3+topic_length+i]=msg[i];
             	}
             	buffer[3+topic_length+i]='\0';
             	printf("%s\n", buffer);
             	n=send(clifd,buffer, 3+topic_length+i, 0);
             	
             }
             else{
                buffer[0]=56;
             	buffer[1]=topic_length<<4;
             	buffer[1]+=len>>8;
             	buffer[2]=len^((len<<8)-1);
             	
             	int i=0;
             	for(;i<topic_length;i++){
             	    buffer[3+i]=topic[i];
             	}
             	buffer[3+i]='\0';
             	n=send(clifd,buffer, strlen(buffer), 0);
             }
             printf("%s\n", msg);
             return 1;
             
         }
         else if(buffer[0]==64){
             printf("Connection Termination request received\n");
             //Sending Disconnection Acknowledgement
             bzero(buffer, sizeof(buffer));
             buffer[0]=72;
             buffer[1]='\0';
             n=send(clifd, buffer, strlen(buffer), 0);
             return 2;
         }
         
     }
     return 0;
 }
             
             
             
             
             
             
             
             
             
             
             
             
             
