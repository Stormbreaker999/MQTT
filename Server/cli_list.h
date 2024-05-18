struct client_list{
    int cli_id;
    struct sockaddr_in addr;
    struct client_list* next;
}
