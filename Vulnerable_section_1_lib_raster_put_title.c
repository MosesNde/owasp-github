     if (!out) {
         fclose(in);
         G_warning(_("G_put_title - can't create a temp file"));
         return -1;
     }
 
     if (line < 3) {
         G_warning(_("category information for [%s] in [%s] invalid"), name,
                   mapset);
         return -1;
     }
 
     in = fopen(tempfile, "r");
     if (!in) {
         G_warning(_("G_put_title - can't reopen temp file"));
         return -1;
     }
 
         fclose(in);
         G_warning(_("can't write category information for [%s] in [%s]"), name,
                   mapset);
         return -1;
     }
 
     fclose(in);
     fclose(out);
     remove(tempfile);
 
     return 1;
 }