     void* data = NULL;
     status = ov_tensor_data(tensor, &data);
     if (status != OK) {
        ov_shape_free(&output_shape);
         free(results);
         return NULL;
     }