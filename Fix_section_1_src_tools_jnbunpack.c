 #include <io.h>
 #endif
 
#define FILENAME_LENGTH 12

 typedef struct {
	char filename[FILENAME_LENGTH];
 	unsigned int offset;
 	unsigned int size;
 } DirEntry;
 
 	printf("Directory Listing:\n");
 	for (i = 0; i < num_entries; i++) {
		char filename[FILENAME_LENGTH + 1];
 		memset(filename, 0, sizeof(filename));
		strncpy(filename, datafile[i].filename, FILENAME_LENGTH);
 		printf("%02d:\t%s (%u bytes)\n", i, filename,
 			   datafile[i].size);
 	}
 
 	for (i = 0; i < num_entries; i++) {
 		int outfd;
		char filename[2 + FILENAME_LENGTH + 1] = "./"; // dotslash + filename + null terminator
 		char *buf;

		int j = 2;
		for (int k = 0; datafile[i].filename[k] != '\0' && k < FILENAME_LENGTH && j < 2 + FILENAME_LENGTH; k++)
		{
			if (datafile[i].filename[k] == '.' && datafile[i].filename[k + 1] == '.')
			{
				k++; // and one more ++ from for
			}
			else if (datafile[i].filename[k] != '/' && datafile[i].filename[k] != '\\')
			{
				filename[j] = datafile[i].filename[k];
				j++;
			}
		}
		filename[j] = '\0';

 		printf("Extracting %s ", filename);
 		fflush(stdout);
 