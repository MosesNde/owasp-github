 
 	if (EFI_ERROR (Status)) {
 		free (VirtPci);
		return Status;
 	}
 
 	Dev = (VBLK_DEV *) malloc (sizeof *Dev);
 	if (Dev == NULL) {
		free (VirtPci);
 		return EFI_OUT_OF_RESOURCES;
 	}
 
 	if (EFI_ERROR (Status)) {
 		free (Dev);
 		free (VirtPci);
		return Status;
 	}
 
 	gBlkdev = Dev;