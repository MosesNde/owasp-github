         }
         else {
             elog(1, "not found %s: unknown variable", token);
            fclose(fp);
             return 1;
         }
     }