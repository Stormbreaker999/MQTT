#include<stdio.h>
#include<string.h>

int write_to_file(char *topic, char *message){
     char path[20]="./Readings/";
     strcat(path,topic);
     strcat(path, ".txt");
     //printf("%s", path);
     FILE *inp=fopen(path, "a");
     fprintf(inp, "%s$$", message);
     fprintf(inp, "%s","\n");
     fclose(inp);
 }
 
 int read_from_file(char *topic, char *ans){
     char path[20]="./Readings/";
     strcat(path,topic);
     strcat(path, ".txt");
     
     FILE *inp=fopen(path, "r");
     if(inp==NULL) return 0;
     
     char msg[2027];
     int len=0;
     char ch=fgetc(inp);
     while(ch!=EOF){
        
     	
     	int i=0;
     	while(ch!='\n' && ch!=EOF){
     	    msg[i++]=ch;
     	    ch=fgetc(inp);
     	}
     	msg[i]='\0';
     	ch=fgetc(inp);
     	len=i;
     	strcpy(ans,msg);
     	//printf("len%lu", strlen(ans));
     	//printf("%s\n",ans);
     	
     }  
     
     
     return len;
}
