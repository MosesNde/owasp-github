     }
     D_stroke();
 
    if (fontsize < 0) {
        if (length != 0) {
            G_free(label);
        }
         return 0;
    }
 
     /* draw the distance + units text */
 
         D_pos_abs(x_pos + 5 - (tr - tl), y_pos + ysize / 2 + (tt - tb) / 2);
         D_text(label);
     }
    if (length != 0) {
        G_free(label);
    }
 
     return 0;
 }