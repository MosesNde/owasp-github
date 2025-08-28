                 return 0;
               nread = fread (data, sizeof (data), 1, f);
               if (nread == 0)
                return 0;
               goto determine_file_type; /* success */
             }
         }
       errno = 0;
       return 0; /* unknown error */
     }
 
 #else
       /* Seek back over the magic bytes.  */
       if (fseek (f, 0, 0) < 0)
        return 0;
 #endif
     }
 