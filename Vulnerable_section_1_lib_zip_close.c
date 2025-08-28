 
     /* as long as we don't support non-seekable output, clear data descriptor bit */
     if ((is_zip64 = _zip_dirent_write(za, de, flags)) < 0) {
         return -1;
     }
 
     if ((offdata = zip_source_tell_write(za->src)) < 0) {
         zip_error_set_from_source(&za->error, za->src);
         return -1;
     }
 