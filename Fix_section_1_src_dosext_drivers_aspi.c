   cdb->sg_hd.reply_len = out_len;
 
   status = write(fd, cdb, in_len);
  if (status < 0 || status != in_len) {
    ret = -1;
    goto done;
  }
 
   do {
     status = read(fd, si, out_len);
   } while (status == -1 && errno == EINTR);
 
   ret = si->peripheral_device_type;

done:
   free(cdb);
   free(si);
   close(fd);