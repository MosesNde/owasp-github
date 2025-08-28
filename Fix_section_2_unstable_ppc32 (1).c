 
    if (fstat(fileno(bfd),&file_info) == -1) {
       perror("stat");
      fclose(bfd);
       return(-1);
    }
 
       if (!haddr) {
          fprintf(stderr,"load_raw_image: invalid load address 0x%8.8x\n",
                  vaddr);
         fclose(bfd);
          return(-1);
       }
 