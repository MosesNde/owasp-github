     }
 
     G_free((void *)pixbuf);
    G_free(buf);
     (void)TIFFClose(out);
 
     return (0);