 	if (!pcxBytes)
 	{
 		mtnlogMessage(LOG_ERROR, "Failed to allocate memory for PCX bytes");
 		return;
 	}
 	fread(pcxBytes, fileSize, 1, file);