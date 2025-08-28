     if (indexLength == map->indexLongNbytes * map->nTiles) {
         if (read(map->data_fd, tmp, indexLength) != indexLength) {
             Rast3d_error("Rast3d_readIndex: can't read file");
            Rast3d_free(tmp);
             return 0;
         }
     }
                 tmp2 = Rast3d_malloc(indexLength);
                 if (tmp2 == NULL) {
                     Rast3d_error("Rast3d_readIndex: error in Rast3d_malloc");
                    Rast3d_free(tmp);
                     return 0;
                 }
             }
 
             if (read(map->data_fd, tmp2, indexLength) != indexLength) {
                 Rast3d_error("Rast3d_readIndex: can't read file");
                Rast3d_free(tmp);
                Rast3d_free(tmp2);
                 return 0;
             }
 
     indexLength = map->nTiles * sizeof(long);
     if (write(map->data_fd, tmp, indexLength) != indexLength) {
         Rast3d_error("Rast3d_flush_index: can't write file");
        Rast3d_free(tmp);
         return 0;
     }
 