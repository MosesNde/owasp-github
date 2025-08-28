         }
 
         Rast_close(fd);
        G_free(afbuf);
        G_free(cbuf);
 
         Rast_init_colors(&colors);
         Rast_make_aspect_colors(&colors, -8, 8);