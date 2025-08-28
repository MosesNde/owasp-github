         }
     }
     G_verbose_message(_("Removed duplicates: %d"), ndupl);
    Vect_destroy_line_struct(APoints);
    Vect_destroy_line_struct(BPoints);
    Vect_destroy_cats_struct(ACats);
    Vect_destroy_cats_struct(BCats);
    Vect_destroy_boxlist(List);
 }
 
 /*!