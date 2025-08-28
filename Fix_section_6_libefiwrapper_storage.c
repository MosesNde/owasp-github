 
 err:
 	for (j = 0; j < i; j++) {
		tmp_ret = STORAGE_INTERFACES[j].free(st, handle);
 		if (EFI_ERROR(tmp_ret))
 			ewerr("Failed to unregister %s interface",
			      STORAGE_INTERFACES[j].name);
 	}
 	free(media);
 	return ret;