 #include <unistd.h>
 #include <math.h>
 #include <errno.h>
#include <string.h>
 #include <grass/vector.h>
 #include <grass/glocale.h>
 
     filename = G_tempfile();
     fd = open(filename, O_RDWR | O_CREAT | O_EXCL, 0600);
     RTree = RTreeCreateTree(fd, 0, 2);
    (void)remove(filename);
    G_free(filename);
 
     filename = G_tempfile();
     xpntfd = open(filename, O_RDWR | O_CREAT | O_EXCL, 0600);
    if (xpntfd < 0) {
        close(RTree->fd);
        G_free(filename);
        G_fatal_error(_("Failed to create xpnt temporary file: %s"),
                      strerror(errno));
    }
    (void)remove(filename);
    G_free(filename);
 
     BPoints = Vect_new_line_struct();
     Points = Vect_new_line_struct();
     Vect_destroy_line_struct(Points);
     Vect_destroy_line_struct(BPoints);
     Vect_destroy_cats_struct(Cats);
    Vect_destroy_cats_struct(ErrCats);
     G_verbose_message(_("Breaks: %d"), nbreaks);
 }
 