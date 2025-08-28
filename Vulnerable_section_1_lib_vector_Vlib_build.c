                   n_zero_boundaries);
 
     /* remaining checks are for areas only */
    if (Vect_get_num_primitives(Map, GV_BOUNDARY) == 0)
         return 1;
 
     /* intersecting boundaries -> overlapping areas */
     nerrors = Vect_check_line_breaks(Map, GV_BOUNDARY, Err);
     plus = &(Map->plus);
     if (build > GV_BUILD_NONE && !Map->temporary &&
         Map->format != GV_FORMAT_POSTGIS) {
        G_message(_("Building topology for vector map <%s>..."),
                  Vect_get_full_name(Map));
     }
     plus->with_z = Map->head.with_z;
     plus->spidx_with_z = Map->head.with_z;
 
     if (0 > dig_write_plus_file(&fp, plus)) {
         G_warning(_("Error writing out topo file"));
         return 0;
     }
 
     plus = &(Map->plus);
 
     fprintf(out, "---------- TOPOLOGY DUMP ----------\n");
    fprintf(out, "Map:             %s\n", Vect_get_full_name(Map));
     fprintf(out, "Topology format: ");
     if (Map->format == GV_FORMAT_NATIVE)
         fprintf(out, "native");
  */
 int Vect_build_sidx_from_topo(struct Map_info *Map)
 {
    G_debug(3, "Vect_build_sidx_from_topo(): name=%s", Vect_get_full_name(Map));
 
     G_warning(_("%s is no longer supported"), "Vect_build_sidx_from_topo()");
 