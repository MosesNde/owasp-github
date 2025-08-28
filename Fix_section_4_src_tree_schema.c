         if (buffer) {
             strcpy(buffer, "/");
         } else {
            free(path);
             path = strdup("/");
         }
     }