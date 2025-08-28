     sort_cell_stats(do_sort);
     print_cell_stats(fmt, with_percents, with_counts, with_areas, with_labels,
                      fs);
    for (i = 0; i < nfiles; i++) {
        G_free(cell[i]);
    }
    G_free(cell);
 
     return 0;
 }