 
    if (elf_version(EV_CURRENT) == EV_NONE) {
       fprintf(stderr,"load_elf_image: library out of date\n");
      close(fd);
       return(-1);
    }
 
    if (!(img_elf = elf_begin(fd,ELF_C_READ,NULL))) {
       fprintf(stderr,"load_elf_image: elf_begin: %s\n",
               elf_errmsg(elf_errno()));
      close(fd);
       return(-1);
    }
 
    if (!(ehdr = elf32_getehdr(img_elf))) {
       fprintf(stderr,"load_elf_image: invalid ELF file\n");
      elf_end(img_elf);
      close(fd);
       return(-1);
    }
 
 
    if (!bfd) {
       perror("load_elf_image: fdopen");
      elf_end(img_elf);
      close(fd);
       return(-1);
    }
 
             if (!haddr) {
                fprintf(stderr,"load_elf_image: invalid load address 0x%x\n",
                        vaddr);
               elf_end(img_elf);
               fclose(bfd);
                return(-1);
             }
 