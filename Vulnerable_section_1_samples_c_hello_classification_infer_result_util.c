     void* data = NULL;
     status = ov_tensor_data(tensor, &data);
     if (status != OK) {
         free(results);
         return NULL;
     }