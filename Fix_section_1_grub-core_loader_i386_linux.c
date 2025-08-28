 					    GRUB_RELOCATOR_PREFERENCE_HIGH,
 					    1);
     if (err)
      goto fail;
     initrd_mem = get_virtual_current_address (ch);
     initrd_mem_target = get_physical_target_address (ch);
   }