 #include "wheel.h"
 
struct Wheel *get_wheel_file(const char *basepath, const char *name, char *to_match[], unsigned match_mode) {
     DIR *dp;
     struct dirent *rec;
     struct Wheel *result = NULL;
         }
 
         result = calloc(1, sizeof(*result));
         result->path_name = realpath(package_path, NULL);
         result->file_name = strdup(rec->d_name);
 
         size_t parts_total;
         char **parts = split(filename, "-", 0);
         for (parts_total = 0; parts[parts_total] != NULL; parts_total++);
        if (parts_total < 6) {
             // no build tag
             result->distribution = strdup(parts[0]);
             result->version = strdup(parts[1]);
             result->build_tag = NULL;
             result->python_tag = strdup(parts[2]);
             result->abi_tag = strdup(parts[3]);
             result->platform_tag = strdup(parts[4]);
        } else {
             // has build tag
             result->distribution = strdup(parts[0]);
             result->version = strdup(parts[1]);
             result->build_tag = strdup(parts[2]);
             result->python_tag = strdup(parts[3]);
             result->abi_tag = strdup(parts[4]);
             result->platform_tag = strdup(parts[5]);
         }
         GENERIC_ARRAY_FREE(parts);
         break;
     }
     closedir(dp);
     return result;
 }