     }
 
     if (optimize_client_socket(client_sock) == WEBSOCKET_ERRORCODE_FATAL_ERROR) {
         return WEBSOCKET_ERRORCODE_CONTINUABLE_ERROR;
     }
 