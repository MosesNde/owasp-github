 		return EFI_INVALID_PARAMETER;
 
 	ret = locate_handle_buffer(ByProtocol, Protocol, NULL, &nb_handle, &handles);
	if (EFI_ERROR(ret) || nb_handle == 0) {
		if (handles) {
			free(handles);
		}
 		return EFI_NOT_FOUND;
	}
 
 	for (i = 0; i < nb_handle; i++) {
 		ret = handle_protocol(handles[i], &dp_guid, (VOID **)&path);