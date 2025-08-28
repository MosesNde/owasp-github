         if (mergedSz > 0) {
             /* Copy over concatenated octet strings into data buffer */
             XMEMCPY(&data[*idx], mergedData, mergedSz);
         }
     }
 
    XFREE(mergedData, pkcs12->heap, DYNAMIC_TYPE_PKCS);

     return ret;
 }
 #endif