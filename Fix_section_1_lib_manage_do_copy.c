     int i, ret;
     char path[GPATH_MAX], path2[GPATH_MAX];
     int result = 0;
    char *mname = G_fully_qualified_name(old, mapset);
 
     G_debug(3, "Copy %s", list[n].alias);
 
     G_message(_("Copying %s <%s> to current mapset as <%s>"), list[n].maindesc,
              mname, new);
 
     M__hold_signals(1);
     if (G_strcasecmp(list[n].alias, "vector") == 0) {
         ret = Vect_copy(old, mapset, new);
         if (ret == -1) {
            G_warning(_("Unable to copy <%s> to current mapset as <%s>"), mname,
                      new);
             result = 1;
         }
     }
             G_file_name(path2, list[n].element[i], new, G_mapset());
             if (G_recursive_copy(path, path2) == 1) {
                 G_warning(_("Unable to copy <%s> to current mapset as <%s>"),
                          mname, new);
                 result = 1;
             }
             else {
         G_remove(colr2, new);
     }
     M__hold_signals(0);
    G_free(mname);
 
     return result;
 }