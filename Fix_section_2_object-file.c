   strbuf_init(&blank.obj_path, 0);
   strbuf_init(&blank.metadata, 0);
 
   memcpy(of, &blank, sizeof(blank));
 }
 
   }
 }
 
int decompress_object_file(const char *hash) {
   char path[PATH_MAX] = {0};
   get_object_path(path, hash);
 
   FILE *file = fopen(path, "rb");
   if (!file) {
    error("Failed to open file %s: %s", path, strerror(errno));
    return -1;
   }
 
   /**
 
   int ret = inflateInit(&strm);
   if (ret != Z_OK) {
    fclose(file);
    error("Failed to initialize zlib stream");
    return -1;
   }
 
   /**
      */
     strm.avail_in = fread(in_buffer, 1, CHUNK, file);
     if (ferror(file)) {
      fclose(file);
       (void)inflateEnd(&strm);
      error("Error handling file stream in decompression");
      return -1;
     }
     /**
      * avail_in == 0 is equivalient to no more input data being left to process.
       strm.avail_out = CHUNK;
       strm.next_out = out_buffer;
       ret = inflate(&strm, Z_NO_FLUSH);
       switch (ret) {
       case Z_NEED_DICT:
         ret = Z_DATA_ERROR;
       case Z_DATA_ERROR:
       case Z_MEM_ERROR:
      case Z_STREAM_ERROR:
        fclose(file);
         (void)inflateEnd(&strm);
        return -1;
       }
       strbuf_addstr(&sb, (char *)out_buffer, CHUNK - strm.avail_out);
     } while (strm.avail_out == 0);
   char *removed_meta_obj = strchr(sb.buf, '\0') + 1;
   fwrite(removed_meta_obj, 1, sb.len, stdout);
   (void)inflateEnd(&strm);
  fclose(file);
 
   strbuf_release(&sb);
 
  return 0;
 }
 
 int compress_file_to_obj_file(struct object_file *of, const char *path) {