 }
 
 void decompress_object_file(const char *hash) {
  char path[PATH_MAX] = {0};
   get_object_path(path, hash);
 
   FILE *file = fopen(path, "rb");
   return;
 }
 
int compress_file_to_obj_file(const char *path) {
  char metadata[METADATA_MAX] = {0};
  char dir_path[PATH_MAX] = {0};
  char obj_path[PATH_MAX] = {0};
  if (hash_object_file(metadata, obj_path, dir_path, path) != 0) {
    return -1;
   }
 
   create_dir(dir_path);
 
  FILE *file = fopen(path, "rb");
  if (!file) {
    perror("");
    return -1;
  }
 
   FILE *obj_file = fopen(obj_path, "wb");
   if (!obj_file) {
    fclose(file);
    perror("");
    return -1;
   }
 
   int ret, flush;
   if (ret != Z_OK) {
     fclose(file);
     fclose(obj_file);
    error("Failed to initialize zlib");
    return -1;
   }
   /**
    * Append the metadata to the in buffer to get compressed
   strm.avail_out = CHUNK;
   strm.next_out = out;
   ret = deflate(&strm, Z_NO_FLUSH);
  if (ret == Z_STREAM_ERROR) {
    fclose(file);
    fclose(obj_file);
    die("A zlib error occurred");
  }
   have = CHUNK - strm.avail_out;
   if (fwrite(out, 1, have, obj_file) != have || ferror(obj_file)) {
     (void)deflateEnd(&strm);
    fclose(file);
    fclose(obj_file);
    return -1;
   }
 
   do {
       (void)deflateEnd(&strm);
       fclose(file);
       fclose(obj_file);
      return -1;
     }
     flush = feof(file) ? Z_FINISH : Z_NO_FLUSH;
     strm.next_in = in;
       have = CHUNK - strm.avail_out;
       if (fwrite(out, 1, have, obj_file) != have || ferror(obj_file)) {
         (void)deflateEnd(&strm);
        fclose(file);
        fclose(obj_file);
        return -1;
       }
     } while (strm.avail_out == 0);
   } while (flush != Z_FINISH);
   fclose(file);
   fclose(obj_file);
 
  return 0;
 }
 
 // TODO: add buffer param to return hash, bc of -w flag
   printf("dir_path: %s\n", dir_path);
   printf("obj_path: %s\n", obj_path);
 
  return 0;
 }
 
 int compress_buf(const char *buf, size_t size, const char *path_to_write) {