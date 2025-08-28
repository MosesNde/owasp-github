 	readsize = fread(in, size, 1, rndfile);
 	if (readsize != 1) {
 		fprintf(stderr, "Can't read file [/dev/urandom]\n");
		fclose(rndfile);
 		return 1;
 	}
 