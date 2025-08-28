                 char *prefix = "attachment;filename=";
                 if (osStrncmp(value, prefix, osStrlen(prefix)) == 0)
                 {
                    const char *filename = &value[osStrlen(prefix)];
                    // search for PATH_SERPERATOR_LINUX / PATH_SERPERATOR_LINUX and replace with null
                    char *p1 = osStrchr(filename, PATH_SEPARATOR_LINUX);
                    char *p2 = osStrchr(filename, PATH_SEPARATOR_WINDOWS);
                    if (p1)
                    {
                        *p1 = '\0';
                    }
                    if (p2)
                    {
                        *p2 = '\0';
                    }

                     char *folder;
                     switch (ctx->client_ctx->settings->internal.toniebox_firmware.boxIC)
                     {