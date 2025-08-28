 #include <unistd.h>
 #include <math.h>
 #include <errno.h>
 #include <grass/vector.h>
 #include <grass/glocale.h>
 
     filename = G_tempfile();
     fd = open(filename, O_RDWR | O_CREAT | O_EXCL, 0600);
     RTree = RTreeCreateTree(fd, 0, 2);
    remove(filename);
 
     filename = G_tempfile();
     xpntfd = open(filename, O_RDWR | O_CREAT | O_EXCL, 0600);
    remove(filename);
 
     BPoints = Vect_new_line_struct();
     Points = Vect_new_line_struct();
     Vect_destroy_line_struct(Points);
     Vect_destroy_line_struct(BPoints);
     Vect_destroy_cats_struct(Cats);
     G_verbose_message(_("Breaks: %d"), nbreaks);
 }
 