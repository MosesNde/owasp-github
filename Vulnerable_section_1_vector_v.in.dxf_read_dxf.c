     struct dxf_file *dxf;
 
     dxf = (struct dxf_file *)G_malloc(sizeof(struct dxf_file));
 
     dxf->name = G_store(file);
    if (!(dxf->fp = fopen(file, "r")))
         return NULL;

     /* get the file size */
     G_fseek(dxf->fp, 0L, SEEK_END);
     dxf->size = G_ftell(dxf->fp);