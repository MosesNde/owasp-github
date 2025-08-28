 
    start = strtoul(argv[3],NULL,0);
 
   if ((fd = open(argv[1],O_RDONLY)) == -1)
      return(-1);
 
    if (elf_version(EV_CURRENT) == EV_NONE) {
      fprintf(stderr,"load_elf_image: library out of date\n");
      return(-1);
    }
 
    if (!(img_elf = elf_begin(fd,ELF_C_READ,NULL))) {
      fprintf(stderr,"load_elf_image: elf_begin: %s\n",
              elf_errmsg(elf_errno()));
      return(-1);
    }
 
    if (!(phdr = elf32_getphdr(img_elf))) {
      fprintf(stderr,"load_elf_image: elf32_getphdr: %s\n",
              elf_errmsg(elf_errno()));
      return(-1);
    }
 
    if (!(fd_out = fopen(argv[2],"w"))) {
       fprintf(stderr,"Unable to create file \"%s\"\n",argv[2]);
      exit(EXIT_FAILURE);
    }
 
   ehdr = elf32_getehdr(img_elf);
   phdr = elf32_getphdr(img_elf);

    printf("Extracting ROM from ELF file '%s'...\n",argv[1]);
    bfd = fdopen(fd,"r");
 
    if (!bfd) {
      perror("load_elf_image: fdopen");
      return(-1);
    }
 
    for(i=0;i<ehdr->e_phnum;i++,phdr++)
    {
       if (fseek(bfd,phdr->p_offset,SEEK_SET) != 0) {
          perror("fseek");
         return(-1);
       }
 
       vaddr = (m_uint64_t)phdr->p_vaddr;
       }
    }
 
    fclose(fd_out);
    return(0);
 }