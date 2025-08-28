   ARCH_ELFDATA_DEF;
 
   dyn = lib_malloc(shdr->sh_size);
  if (dyn == NULL)
    {
      berr("Failed to allocate memory for elf dynamic section\n");
      return -ENOMEM;
    }

   ret = modlib_read(loadinfo, (FAR uint8_t *)dyn, shdr->sh_size,
                     shdr->sh_offset);
   if (ret < 0)
     {
       berr("Failed to read dynamic section header");
      lib_free(dyn);
       return ret;
     }
 