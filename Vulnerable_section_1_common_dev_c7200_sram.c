    /* Allocate the private data structure for SRAM */
    if (!(d = malloc(sizeof(*d)))) {
       fprintf(stderr,"dev_c7200_sram_init (%s): out of memory\n",name);
      return(-1);
    }
 
    memset(d,0,sizeof(*d));
    d->vm_obj.data = d;
    d->vm_obj.shutdown = (vm_shutdown_t)dev_c7200_sram_shutdown;
 
   if (!(d->filename = vm_build_filename(vm,name)))
      return(-1);
 
    /* add as a pci device */
    d->pci_dev = pci_dev_add_basic(pci_bus,name,
                                   PCI_VENDOR_SRAM,PCI_PRODUCT_SRAM,
                                   pci_device,0);
 
    alias_paddr = 0x100000000ULL + paddr;
    
    /* create the standard RAM zone */
    if (!(d->dev = dev_create_ram(vm,name,FALSE,d->filename,paddr,len))) {
       fprintf(stderr,"dev_c7200_sram_init: unable to create '%s' file.\n",
               d->filename);
      return(-1);
    }
 
    /* create the RAM alias */
    if (!(d->alias_dev_name = dyn_sprintf("%s_alias",name))) {
       fprintf(stderr,"dev_c7200_sram_init: unable to create alias name.\n");
      return(-1);
    }
 
    d->alias_dev = dev_create_ram_alias(vm,d->alias_dev_name,name,
                                        alias_paddr,len);
 
    if (!d->alias_dev) {
       fprintf(stderr,"dev_c7200_sram_init: unable to create alias device.\n");
      return(-1);
    }
 
    /* create the byte-swapped zone (used with Galileo DMA) */
    if (!(d->bs_dev_name = dyn_sprintf("%s_bswap",name))) {
       fprintf(stderr,"dev_c7200_sram_init: unable to create BS name.\n");
      return(-1);
    }
 
    if (dev_bswap_init(vm,d->bs_dev_name,paddr+0x800000,len,paddr) == -1) {
       fprintf(stderr,"dev_c7200_sram_init: unable to create BS device.\n");
      return(-1);
    }
    
    d->bs_obj = vm_object_find(vm,d->bs_dev_name);
    return(0);
 }    