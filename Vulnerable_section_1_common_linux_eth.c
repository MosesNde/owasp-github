 
    if (bind(sck,(struct sockaddr *)&sa,sizeof(struct sockaddr_ll)) == -1) {
       fprintf(stderr,"eth_init_socket: bind: %s\n",strerror(errno));
       return(-1);
    }
 
    if (setsockopt(sck,SOL_PACKET,PACKET_ADD_MEMBERSHIP,
                   &mreq,sizeof(mreq)) == -1) 
    {
       fprintf(stderr,"eth_init_socket: setsockopt: %s\n",strerror(errno));
       return(-1);
    }
 