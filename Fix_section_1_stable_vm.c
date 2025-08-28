  err_reg_add:
    vm_close_log(vm);
  err_log:
   vm_release_lock(vm,TRUE);
  err_lock:
    free(vm->rommon_vars.filename);
  err_rommon: