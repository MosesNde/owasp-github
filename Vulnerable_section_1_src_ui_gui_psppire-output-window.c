 
 #include <config.h>
 
#include <gtk/gtksignal.h>
#include <gtk/gtkbox.h>
#include "helper.h"

#include <libpspp/cast.h>
#include <libpspp/message.h>
#include <libpspp/string-map.h>
#include <output/cairo.h>
#include <output/chart-item.h>
#include <output/driver-provider.h>
#include <output/output-item.h>
#include <output/table-item.h>
#include <output/text-item.h>
#include <output/tab.h>
 #include <stdlib.h>

#include "help-menu.h"

#include "psppire-output-window.h"


#include "xalloc.h"

#include <sys/types.h>
 #include <sys/stat.h>
 #include <unistd.h>
 
 #include <gettext.h>
 #define _(msgid) gettext (msgid)
 #define N_(msgid) msgid
   gsize length;
   gchar *text = NULL;
   struct output_driver *driver = NULL;
  char *filename = NULL;
   struct string_map options;
 
   GtkTreeSelection *sel = gtk_tree_view_get_selection (window->overview);
   if ( n == NULL)
     return;
 
   string_map_init (&options);
  filename = tempnam (NULL, NULL);
   string_map_insert (&options, "output-file", filename);
 
   switch (info)
 
   unlink (filename);
   free (filename);
 
   g_list_free (rows);
 }