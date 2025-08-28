     }
     D_stroke();
 
    if (fontsize < 0)
         return 0;
 
     /* draw the distance + units text */
 
         D_pos_abs(x_pos + 5 - (tr - tl), y_pos + ysize / 2 + (tt - tb) / 2);
         D_text(label);
     }
 
     return 0;
 }