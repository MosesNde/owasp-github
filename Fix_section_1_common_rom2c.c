 
    start = strtoul(argv[3],NULL,0);
 
   if ((fd = open(argv[1],O_RDONLY)) == -1) {
      perror("open");
      goto err_open;
   }
 
    if (elf_version(EV_CURRENT) == EV_NONE) {
      fprintf(stderr,"elf_version: library out of date\n");
      goto err_elf_version;
    }
 
    if (!(img_elf = elf_begin(fd,ELF_C_READ,NULL))) {
      fprintf(stderr,"elf_begin: %s\n",elf_errmsg(elf_errno()));
      goto err_elf_begin;
    }
 
    if (!(phdr = elf32_getphdr(img_elf))) {
      fprintf(stderr,"elf32_getphdr: %s\n",elf_errmsg(elf_errno()));
      goto err_elf32_getphdr;
   }

   if (!(ehdr = elf32_getehdr(img_elf))) {
      fprintf(stderr,"elf32_getehdr: %s\n",elf_errmsg(elf_errno()));
      goto err_elf32_getehdr;
    }
 
    if (!(fd_out = fopen(argv[2],"w"))) {
       fprintf(stderr,"Unable to create file \"%s\"\n",argv[2]);
      goto err_fopen;
    }
 
    printf("Extracting ROM from ELF file '%s'...\n",argv[1]);
    bfd = fdopen(fd,"r");
 
    if (!bfd) {
      perror("fdopen");
      goto err_fdopen;
    }
 
    for(i=0;i<ehdr->e_phnum;i++,phdr++)
    {
       if (fseek(bfd,phdr->p_offset,SEEK_SET) != 0) {
          perror("fseek");
         goto err_fseek;
       }
 
       vaddr = (m_uint64_t)phdr->p_vaddr;
       }
    }
 
   fclose(bfd);
    fclose(fd_out);
   elf_end(img_elf);
    return(0);

err_fseek:
   fclose(bfd); // instead of close(fd)
   fclose(fd_out);
   elf_end(img_elf);
   return(EXIT_FAILURE);
err_fdopen:
   fclose(fd_out);
err_fopen:
err_elf32_getehdr:
err_elf32_getphdr:
   elf_end(img_elf);
err_elf_begin:
err_elf_version:
   close(fd);
err_open:
   return(EXIT_FAILURE);
 }