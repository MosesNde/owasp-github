 out_debugfs_remove:
 	blk_debugfs_remove(disk);
 	mutex_unlock(&q->sysfs_lock);
	if (queue_is_mq(q))
		blk_mq_sysfs_unregister(disk);
 out_put_queue_kobj:
 	kobject_put(&disk->queue_kobj);
 	return ret;