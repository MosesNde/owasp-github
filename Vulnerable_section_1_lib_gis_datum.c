     qsort(table.datums, table.count, sizeof(struct datum), compare_table_names);
 
     G_initialize_done(&table.initialized);
 }
 
 static int compare_table_names(const void *aa, const void *bb)