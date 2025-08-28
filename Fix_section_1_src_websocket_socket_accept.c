     }
 
     if (optimize_client_socket(client_sock) == WEBSOCKET_ERRORCODE_FATAL_ERROR) {
        websocket_close(client_sock);
         return WEBSOCKET_ERRORCODE_CONTINUABLE_ERROR;
     }
 