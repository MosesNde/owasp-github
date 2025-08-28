 		ret = elv_register_queue(q, false);
 		if (ret) {
 			mutex_unlock(&q->sysfs_lock);
			if (q->mq_ops)
				blk_mq_unregister_dev(dev, q);
 			mutex_unlock(&queue_to_wrapper(q)->sysfs_dir_lock);
 			kobject_del(&q->kobj);
 			blk_trace_remove_sysfs(dev);