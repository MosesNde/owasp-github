   else if ( class == CLASS_UNIVERSAL && tag == TAG_SET && constructed )
     rootca = 1;
   else
    {
      err = gpg_error (GPG_ERR_INV_OBJ);
      goto leave;
    }
   totobjlen = objlen + hdrlen;
   log_assert (totobjlen <= buflen);
 
       if (err)
         goto leave;
       if ( !(class == CLASS_UNIVERSAL && tag == TAG_SEQUENCE && constructed) )
        {
          err = gpg_error (GPG_ERR_INV_OBJ);
          goto leave;
        }
       totobjlen = objlen + hdrlen;
       log_assert (save_p + totobjlen <= buffer + buflen);
       memmove (buffer, save_p, totobjlen);
                 continue;
             }
 
          /* Found.  Return but save the last index of the loop.  */
           *idx_p = idx;
           return 0;
         }