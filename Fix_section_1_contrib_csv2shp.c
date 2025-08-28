     if (delimiter == sbuffer[strlen(sbuffer) - 1])
     {
         fprintf(stderr, "lines must not end with the delimiter character\n");
        fclose(csv_f);
         return EXIT_FAILURE;
     }
 
     if (n_columns > MAX_COLUMNS)
     {
         fprintf(stderr, "too many columns, maximum is %i\n", MAX_COLUMNS);
        fclose(csv_f);
         return EXIT_FAILURE;
     }
 
                     "Number of columns on row %i does not match number of "
                     "columns on row 1\n",
                     n_columns);
            fclose(csv_f);
             return EXIT_FAILURE;
         }
     }
     {
         fprintf(stderr, "The header row must define one each a column named "
                         "longitude and latitude\n");
        fclose(csv_f);
         return EXIT_FAILURE;
     }
 
 
     printf("Initializing output files...\n");
 
     SHPHandle shp_h = SHPCreate(argv[3], SHPT_POINT);
     DBFHandle dbf_h = DBFCreate(argv[3]);
     if (NULL == dbf_h)
     {
         fprintf(stderr, "DBFCreate failed\n");
        SHPClose(shp_h);
        fclose(csv_f);
         exit(EXIT_FAILURE);
     }
 
                               columns[x].nDecimals))
         {
             fprintf(stderr, "DBFFieldAdd failed column %i\n", x + 1);
            SHPClose(shp_h);
            DBFClose(dbf_h);
            fclose(csv_f);
             exit(EXIT_FAILURE);
         }
     }
             if (!b)
             {
                 fprintf(stderr, "DBFWrite*Attribute failed\n");
                SHPClose(shp_h);
                DBFClose(dbf_h);
                fclose(csv_f);
                 exit(EXIT_FAILURE);
             }
         }