   }
 
   uri_hier_part = g_strstr_len (uri, -1, ":");
   while (*uri_hier_part == ':' || *uri_hier_part == '/') {
     uri_hier_part++;
   }