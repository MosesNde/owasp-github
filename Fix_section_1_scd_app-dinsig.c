   else if ( class == CLASS_UNIVERSAL && tag == TAG_SET && constructed )
     rootca = 1;
   else
    {
      err = gpg_error (GPG_ERR_INV_OBJ);
      goto leave;
    }
   totobjlen = objlen + hdrlen;
   log_assert (totobjlen <= buflen);
 