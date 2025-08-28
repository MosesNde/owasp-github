    fseek(infile, 0, SEEK_SET);
    if (total_size < 0) {
       printf("ERROR: Could not get the input file size.\n");
       return -1;
    }
    
    // Read in the header
    size_t result = fread(&header, sizeof(HEADER), 1, infile);
    if (result < 0) {
       printf("ERROR: Could not read the input file header.\n");
       return -1;
    }
    