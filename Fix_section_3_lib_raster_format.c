     if (old) {
         n = ((unsigned int)nrows + 1) * sizeof(off_t);
         if (read(fd, row_ptr, n) != n)
            return -1;
         return 1;
     }
 
      */
 
     if (read(fd, &nbytes, 1) != 1)
        return -1;
     if (nbytes == 0)
        return -1;
 
     n = ((unsigned int)nrows + 1) * nbytes;
     buf = G_malloc(n);
     return 1;
 
 badread:
    G_free(buf);
     return -1;
 }
 