     if (fread(&ehdr, 1, sizeof(ElfW(Ehdr)), file) != sizeof(ElfW(Ehdr))) {
         // failed to read elf header
         free(program_path);
         assert(trait->is_true==FALSE);
         return 1;
     }
         ehdr.e_ident[EI_MAG3] != ELFMAG3) {
         //Not a valid ELF file
         free(program_path);
         assert(trait->is_true==FALSE);
         return 1;
     }
         // did not find the symbol table or the string table with the names
         assert(trait->is_true==FALSE);
         free(program_path);
         return 1;
     }
 
             free(symbols);
             free(strtab_data);
             free(program_path);

             return 0;
         }
     }
 
     free(symbols);
     free(strtab_data);
     free(program_path);
     assert(trait->is_true==FALSE);
     printf("Library: %s: DOES NOT have the Trait (even in static symbol table)\n", "(main Binary)");
     return 1;