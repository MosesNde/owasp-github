     if (delimiter == sbuffer[strlen(sbuffer) - 1])
     {
         fprintf(stderr, "lines must not end with the delimiter character\n");
         return EXIT_FAILURE;
     }
 
     if (n_columns > MAX_COLUMNS)
     {
         fprintf(stderr, "too many columns, maximum is %i\n", MAX_COLUMNS);
         return EXIT_FAILURE;
     }
 
                     "Number of columns on row %i does not match number of "
                     "columns on row 1\n",
                     n_columns);
             return EXIT_FAILURE;
         }
     }
     {
         fprintf(stderr, "The header row must define one each a column named "
                         "longitude and latitude\n");
         return EXIT_FAILURE;
     }
 
 
     printf("Initializing output files...\n");
 
    // TODO(schwehr): Close csv_f, shp_h, and dbf_h before EXIT_FAILURE
     SHPHandle shp_h = SHPCreate(argv[3], SHPT_POINT);
     DBFHandle dbf_h = DBFCreate(argv[3]);
     if (NULL == dbf_h)
     {
         fprintf(stderr, "DBFCreate failed\n");
         exit(EXIT_FAILURE);
     }
 
                               columns[x].nDecimals))
         {
             fprintf(stderr, "DBFFieldAdd failed column %i\n", x + 1);
             exit(EXIT_FAILURE);
         }
     }
             if (!b)
             {
                 fprintf(stderr, "DBFWrite*Attribute failed\n");
                 exit(EXIT_FAILURE);
             }
         }