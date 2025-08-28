     if (old) {
         n = ((unsigned int)nrows + 1) * sizeof(off_t);
         if (read(fd, row_ptr, n) != n)
            goto badread;
         return 1;
     }
 
      */
 
     if (read(fd, &nbytes, 1) != 1)
        goto badread;
     if (nbytes == 0)
        goto badread;
 
     n = ((unsigned int)nrows + 1) * nbytes;
     buf = G_malloc(n);
     return 1;
 
 badread:
     return -1;
 }
 