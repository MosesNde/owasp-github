   }
 
   uri_hier_part = g_strstr_len (uri, -1, ":");
  if (!uri_hier_part)
    return NULL;

   while (*uri_hier_part == ':' || *uri_hier_part == '/') {
     uri_hier_part++;
   }