 
 	// Delete timer
 	HW_TS_Delete(led_timer_id);
	HW_TS_Delete(count_timer_id);
 
 	// Disable charging
 	FS_Charge_SetCurrent(FS_CHARGE_DISABLE);