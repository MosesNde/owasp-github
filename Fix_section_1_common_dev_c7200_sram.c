    /* Allocate the private data structure for SRAM */
    if (!(d = malloc(sizeof(*d)))) {
       fprintf(stderr,"dev_c7200_sram_init (%s): out of memory\n",name);
      goto err_malloc;
    }
 
    memset(d,0,sizeof(*d));
    d->vm_obj.data = d;
    d->vm_obj.shutdown = (vm_shutdown_t)dev_c7200_sram_shutdown;
 
   if (!(d->filename = vm_build_filename(vm,name))) {
      goto err_filename;
   }
 
    /* add as a pci device */
    d->pci_dev = pci_dev_add_basic(pci_bus,name,
                                   PCI_VENDOR_SRAM,PCI_PRODUCT_SRAM,
                                   pci_device,0);
 
   if (!d->pci_dev) {
      fprintf(stderr,"dev_c7200_sram_init: unable to create basic device.\n");
      goto err_pci_dev;
   }

    alias_paddr = 0x100000000ULL + paddr;
    
    /* create the standard RAM zone */
    if (!(d->dev = dev_create_ram(vm,name,FALSE,d->filename,paddr,len))) {
       fprintf(stderr,"dev_c7200_sram_init: unable to create '%s' file.\n",
               d->filename);
      goto err_dev;
    }
 
    /* create the RAM alias */
    if (!(d->alias_dev_name = dyn_sprintf("%s_alias",name))) {
       fprintf(stderr,"dev_c7200_sram_init: unable to create alias name.\n");
      goto err_alias_dev_name;
    }
 
    d->alias_dev = dev_create_ram_alias(vm,d->alias_dev_name,name,
                                        alias_paddr,len);
 
    if (!d->alias_dev) {
       fprintf(stderr,"dev_c7200_sram_init: unable to create alias device.\n");
      goto err_alias_dev;
    }
 
    /* create the byte-swapped zone (used with Galileo DMA) */
    if (!(d->bs_dev_name = dyn_sprintf("%s_bswap",name))) {
       fprintf(stderr,"dev_c7200_sram_init: unable to create BS name.\n");
      goto err_bs_dev_name;
    }
 
    if (dev_bswap_init(vm,d->bs_dev_name,paddr+0x800000,len,paddr) == -1) {
       fprintf(stderr,"dev_c7200_sram_init: unable to create BS device.\n");
      goto err_dev_bswap_init;
    }
    
    d->bs_obj = vm_object_find(vm,d->bs_dev_name);
    return(0);

err_dev_bswap_init:
   free(d->bs_dev_name);
err_bs_dev_name:
   dev_remove(vm,d->alias_dev);
   free(d->alias_dev);
err_alias_dev:
   free(d->alias_dev_name);
err_alias_dev_name:
   dev_remove(vm,d->dev);
   free(d->dev);
   unlink(d->filename);
err_dev:
   pci_dev_remove(d->pci_dev);
err_pci_dev:
   free(d->filename);
err_filename:
   free(d);
err_malloc:
   return(-1);
 }    