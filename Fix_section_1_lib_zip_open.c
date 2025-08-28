         /* If the central directory doesn't start on this disk, we can't check that offset is valid. Check as much as we can instead. */
         if (cd->this_disk < cd->eocd_disk) {
             /* Disks before the start of the central directory don't contain an EOCD. */
            _zip_cdir_free(cd);
             return false;
         }
         if (cd->size <= cd->eocd_offset) {
             /* The complete central directory would fit on this disk. */
            _zip_cdir_free(cd);
             return false;
         }
     }
             /* An empty archive doesn't contain central directory entries. */
         }
         else if (!check_magic(cd->offset, buffer, buf_offset, za->src, CENTRAL_MAGIC)) {
            _zip_cdir_free(cd);
             return false;
         }
     }