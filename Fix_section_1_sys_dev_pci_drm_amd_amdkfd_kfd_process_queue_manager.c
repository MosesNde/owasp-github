 		pr_debug("Queue id %d was restored successfully\n", queue_id);
 
 	kfree(q_data);
	kfree(q_extra_data);
 
 	return ret;
 }