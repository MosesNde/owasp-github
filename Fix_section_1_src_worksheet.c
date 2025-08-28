 
     /* Check that row and col are valid without storing. */
     err = _check_dimensions(self, first_row, first_col, LXW_TRUE, LXW_TRUE);
    if (err) {
        free(selection);
         return err;
    }
 
     err = _check_dimensions(self, last_row, last_col, LXW_TRUE, LXW_TRUE);
    if (err) {
        free(selection);
         return err;
    }
 
     /* Set the cell range selection. Do this before swapping max/min to  */
     /* allow the selection direction to be reversed. */
 
     /* Check and store the cell dimensions. */
     err = _check_dimensions(self, row_num, col_num, LXW_FALSE, LXW_FALSE);
    if (err) {
        fclose(image_stream);
         return err;
    }
 
     /* Create a new object to hold the image properties. */
     object_props = calloc(1, sizeof(lxw_object_properties));