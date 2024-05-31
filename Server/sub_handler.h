#include<string.h>
void send_messages(int *client_list, int clients, char *topic){
    printf("Here");
    char buffer[2048];
    int topic_length=strlen(topic);
    char msg[2025];
    int len=read_from_file(topic, msg);
    printf("%s", msg);

    //Publish 00100000 = 32
    
    for(int i=0;i<clients;i++){
	    bzero(buffer, sizeof(buffer));
	    printf("Sending to %d",i);
	    msg[len-2]='\0';
	    len=strlen(msg);
	    buffer[0]=32;
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
		 	
	    int n=send(4,buffer, 3+topic_length+i, 0);
	
    }
    printf("%d\n", clients);
}


int add_subscription(int cli_id, char *topic){
     char path[20]="./Subs/";
     strcat(path,"subs.txt");
     //printf("%s", path);
     FILE *inp=fopen(path, "a");
     fprintf(inp, "%s$%d$$", topic, cli_id);
     fprintf(inp, "%s","\n");
     fclose(inp);
     return 1;
}

int find_by_topic(int *client_list, char *topic){
     int total=0;
     char path[20]="./Subs/";
     strcat(path,"subs.txt");
     FILE *inp=fopen(path, "r");
     if(inp==NULL) return 0;
     
     char top[10];
     char cl[10];
     char ch=fgetc(inp);
     while(ch!=EOF){
        
     	
     	int i=0;
     	while(ch!='$' && ch!=EOF){
     	    top[i++]=ch;
     	    ch=fgetc(inp);
     	}
     	top[i]='\0';
     	ch=fgetc(inp);
     	i=0;
     	while(ch!='\n' && ch!=EOF){
     	    cl[i++]=ch;
     	    ch=fgetc(inp);
     	}
     	cl[i-2]='\0';
     	if(strcmp(top, topic)==0){
     	    client_list[total++]=atoi(cl);
     	}
     	ch=fgetc(inp);
     	//printf("len%lu", strlen(ans));
     	//printf("%s\n",ans);
     	
     }  
     
     
     return total;
}
