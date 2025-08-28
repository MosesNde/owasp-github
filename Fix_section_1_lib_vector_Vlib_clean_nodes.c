         }
     }
     G_verbose_message(_("Modifications: %d"), nmodif);
    Vect_destroy_line_struct(Points);
    Vect_destroy_cats_struct(OCats);
    Vect_destroy_cats_struct(LCats);
    Vect_destroy_cats_struct(SCats);
 
     return (nmodif);
 }