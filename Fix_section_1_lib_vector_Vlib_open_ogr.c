             Map->mapset);
 
     if (Vect_open_fidx(Map, &(Map->fInfo.ogr.offset)) != 0) {
        const char *map_name = Vect_get_full_name(Map);
         G_warning(_("Unable to open feature index file for vector map <%s>"),
                  map_name);
        G_free((void *)map_name);
         G_zero(&(Map->fInfo.ogr.offset), sizeof(struct Format_info_offset));
     }
 
     dig_file_init(&fp);
     fp.file = G_fopen_old(elem, GV_FIDX_ELEMENT, Map->mapset);
     if (fp.file == NULL) {
        const char *map_name = Vect_get_full_name(Map);
        G_debug(1, "unable to open fidx file for vector map <%s>", map_name);
        G_free((void *)map_name);
         return -1;
     }
 
     /* Header */
    if (0 >= dig__fread_port_C(buf, 5, &fp)) {
        fclose(fp.file);
         return -1;
    }
     Version_Major = buf[0];
     Version_Minor = buf[1];
     Back_Major = buf[2];
 
     /* Body */
     /* bytes 6 - 9 : header size */
    if (0 >= dig__fread_port_L(&length, 1, &fp)) {
        fclose(fp.file);
         return -1;
    }
     G_debug(4, "  header size %ld", length);
 
     G_fseek(fp.file, length, SEEK_SET);
 
     /* number of records  */
    if (0 >= dig__fread_port_I(&(offset->array_num), 1, &fp)) {
        fclose(fp.file);
         return -1;
    }
 
     /* alloc space */
     offset->array = (int *)G_malloc(offset->array_num * sizeof(int));
     offset->array_alloc = offset->array_num;
 
     /* offsets */
    if (0 >= dig__fread_port_I(offset->array, offset->array_num, &fp)) {
        fclose(fp.file);
         return -1;
    }
 
     fclose(fp.file);
 