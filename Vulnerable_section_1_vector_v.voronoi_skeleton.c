             Vect_merge_lines(&Out, GV_LINE, NULL, NULL);
     }
 
    if (thresh >= 0)
         return 0;
 
     for (node = 1; node <= Vect_get_num_nodes(&Out); node++) {
         if (!Vect_node_alive(&Out, node))
         else
             Vect_merge_lines(&Out, GV_LINE, NULL, NULL);
     }
 
     return 0;
 }
             ntied++;
         }
     }
 
     return ntied;
 }