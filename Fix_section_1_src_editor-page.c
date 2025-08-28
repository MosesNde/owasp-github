                                 int        *position,
                                 GtkText    *entry)
 {
  g_autoptr(GString) str = NULL;
   const char *text;
 
   g_assert (EDITOR_IS_PAGE (self));
   g_assert (position != NULL);
   g_assert (GTK_IS_TEXT (entry));
 
   text = gtk_editable_get_text (GTK_EDITABLE (entry));

   str = g_string_new (text);
   g_string_insert_len (str, *position, new_text, length);
 
         continue;
 
       g_signal_stop_emission_by_name (entry, "insert-text");
      break;
     }
 }
 