     }
 
     /* keep track of the overall min and max, excluding null */
    if (Rast_is_d_null_value(&(rule->low.value))) {
        G_free(rule);
         return;
    }
    if (Rast_is_d_null_value(&(rule->high.value))) {
        G_free(rule);
         return;
    }
     min = rule->low.value;
     max = rule->high.value;
     if (min <= max) {