     }
 
     os_detach_thread(core->can_monitor_th);
 }
 
 uint32 can_write(can_message_t* message, disp_mode_t disp_mode, const char* comment)