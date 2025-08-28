 	buffer = malloc(fd_size);
 	if(buffer == NULL) {
 		printf("Failed to allocate memory.\n");
		fclose(source);
 		return 1;
 	}
 
 	if(fread(buffer,1,fd_size,source) != fd_size) {
 		printf("Failed to read file.\n");
		fclose(source);
 		return 1;
 	}
 	fclose(source);