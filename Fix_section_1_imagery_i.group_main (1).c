         if (subgs_num <= 0) {
             fprintf(stdout, _("Group <%s> does not contain any subgroup.\n"),
                     group);
            G_free(subgs);
             return;
         }
         max = 0;