   if (argc != 1) {
     die("Usage: tig cat-file <hash>\n");
   }
  decompress_object_file(argv[0]);
   return 0;
 }