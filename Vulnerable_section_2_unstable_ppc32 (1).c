 
    if (fstat(fileno(bfd),&file_info) == -1) {
       perror("stat");
       return(-1);
    }
 
       if (!haddr) {
          fprintf(stderr,"load_raw_image: invalid load address 0x%8.8x\n",
                  vaddr);
          return(-1);
       }
 