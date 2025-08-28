 
 	if (EFI_ERROR (Status)) {
 		free (VirtPci);
 	}
 
 	Dev = (VBLK_DEV *) malloc (sizeof *Dev);
 	if (Dev == NULL) {
 		return EFI_OUT_OF_RESOURCES;
 	}
 
 	if (EFI_ERROR (Status)) {
 		free (Dev);
 		free (VirtPci);
 	}
 
 	gBlkdev = Dev;