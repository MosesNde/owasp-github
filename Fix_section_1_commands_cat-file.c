   if (argc != 1) {
     die("Usage: tig cat-file <hash>\n");
   }
  if (decompress_object_file(argv[0]) != 0) {
    return -1;
  }
   return 0;
 }