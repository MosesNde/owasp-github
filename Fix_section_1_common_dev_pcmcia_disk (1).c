    else {
       /* new disk */
       if (disk_format(d)) {
         close(d->fd);
         d->fd = -1;
          return(-1);
       }
    }