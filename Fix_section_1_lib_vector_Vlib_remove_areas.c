         *removed_area = size_removed;
 
     G_message(_("%d areas of total size %g removed"), nremoved, size_removed);
    Vect_destroy_list(AList);
    Vect_destroy_list(List);
    Vect_destroy_line_struct(Points);
    Vect_destroy_cats_struct(Cats);
 
     return (nremoved);
 }