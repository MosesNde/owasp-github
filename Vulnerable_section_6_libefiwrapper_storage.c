 
 err:
 	for (j = 0; j < i; j++) {
		tmp_ret = STORAGE_INTERFACES[i].free(st, handle);
 		if (EFI_ERROR(tmp_ret))
 			ewerr("Failed to unregister %s interface",
			      STORAGE_INTERFACES[i].name);
 	}
 	free(media);
 	return ret;