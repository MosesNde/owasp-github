 					    GRUB_RELOCATOR_PREFERENCE_HIGH,
 					    1);
     if (err)
      return err;
     initrd_mem = get_virtual_current_address (ch);
     initrd_mem_target = get_physical_target_address (ch);
   }