 
     matvar->internal->id = dset_id;
     attr_id = H5Aopen_by_name(dset_id, ".", "MATLAB_class", H5P_DEFAULT, H5P_DEFAULT);
    if ( attr_id < 1 ) {
        H5Aclose(attr_id);
         return MATIO_E_FAIL_TO_IDENTIFY;
    }
     type_id = H5Aget_type(attr_id);
     class_str = (char *)calloc(H5Tget_size(type_id) + 1, 1);
     if ( NULL != class_str ) {