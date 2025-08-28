         G_warning("For %d elements requested negative category (ignored, no "
                   "category in output)",
                   negative);
    Vect_destroy_cats_struct(Cats);
    Vect_destroy_cats_struct(NewCats);
    Vect_destroy_line_struct(Points);
 
     return (rclelem);
 }