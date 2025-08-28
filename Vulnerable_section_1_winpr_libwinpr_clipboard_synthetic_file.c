 
 		if (!GetFileInformationByHandle(file->fd, &FileInfo))
 		{
			file->fd = INVALID_HANDLE_VALUE;
 			CloseHandle(file->fd);
 			error = GetLastError();
 			WLog_ERR(TAG, "Get file [%s] information fail: 0x%08" PRIx32, file->local_name, error);
 			return error;