     if (0 != can_status)
     {
         print_error(can_get_error_message(can_status), IS_WRITE_BLOCK, node_id, index, sub_index, comment, disp_mode);
        SDL_free(data);
        fclose(file);
         return ABORT_TRANSFER;
     }
 