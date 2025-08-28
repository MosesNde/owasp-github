   if (linelen == (size_t)(-1))
     {
       error (0, 0, _("%s subprocess I/O error"), progname);
       return NULL;
     }
   if (linelen > 0 && line[linelen - 1] == '\n')