     }
 
     /* keep track of the overall min and max, excluding null */
    if (Rast_is_d_null_value(&(rule->low.value)))
         return;
    if (Rast_is_d_null_value(&(rule->high.value)))
         return;
     min = rule->low.value;
     max = rule->high.value;
     if (min <= max) {