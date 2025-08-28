         plus->built = GV_BUILD_AREAS;
     }
 
    if (build < GV_BUILD_ATTACH_ISLES) {
        Vect_destroy_cats_struct(Cats);
         return 1;
    }
 
     /* Attach isles to areas */
     if (plus->built < GV_BUILD_ATTACH_ISLES) {
         plus->built = GV_BUILD_ATTACH_ISLES;
     }
 
    if (build < GV_BUILD_CENTROIDS) {
        Vect_destroy_cats_struct(Cats);
         return 1;
    }
 
     /* Attach centroids to areas */
     if (plus->built < GV_BUILD_CENTROIDS) {