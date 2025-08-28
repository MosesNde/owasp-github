                 char *prefix = "attachment;filename=";
                 if (osStrncmp(value, prefix, osStrlen(prefix)) == 0)
                 {
                    const char *filename = &value[osStrlen(prefix)]; // TODO path traversal
                     char *folder;
                     switch (ctx->client_ctx->settings->internal.toniebox_firmware.boxIC)
                     {