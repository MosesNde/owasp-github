 out_debugfs_remove:
 	blk_debugfs_remove(disk);
 	mutex_unlock(&q->sysfs_lock);
 out_put_queue_kobj:
 	kobject_put(&disk->queue_kobj);
 	mutex_unlock(&q->sysfs_dir_lock);