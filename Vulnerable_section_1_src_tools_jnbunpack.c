 #include <io.h>
 #endif
 
 typedef struct {
	char filename[12];
 	unsigned int offset;
 	unsigned int size;
 } DirEntry;
 
 	printf("Directory Listing:\n");
 	for (i = 0; i < num_entries; i++) {
		char filename[14];
 		memset(filename, 0, sizeof(filename));
		strncpy(filename, datafile[i].filename, 12);
 		printf("%02d:\t%s (%u bytes)\n", i, filename,
 			   datafile[i].size);
 	}
 
 	for (i = 0; i < num_entries; i++) {
 		int outfd;
		char filename[14];
 		char *buf;
		memset(filename, 0, sizeof(filename));
		strncpy(filename, datafile[i].filename, 12);
 		printf("Extracting %s ", filename);
 		fflush(stdout);
 