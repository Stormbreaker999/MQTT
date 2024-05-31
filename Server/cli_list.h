struct client_list{
    int cli_id;
    struct client_list* next;
};


struct client_list *addnewclient(struct client_list *head, int clifd){
    struct client_list *newclient=malloc(sizeof(struct client_list));
    newclient->cli_id=clifd;
    newclient->next=head;
    return newclient;
}

struct client_list *removeclient(struct client_list *clist, int clifd){
    if(!clist){
        printf("Error occurred in removing client\n");
        printf("Exitting");
        exit(0);
    }
    if(clist->cli_id==clifd){
    	struct client_list *temp=clist->next;
    	free(clist);
        return temp;
    }
    else{
        struct client_list *ptr=clist;
        while(ptr && ptr->next && ptr->next->cli_id!=clifd) ptr=ptr->next;
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

  
    
    
    
