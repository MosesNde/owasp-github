 	printk(KERN_INFO "driver %s\n", hcd_name);
 	workqueue = create_singlethread_workqueue("u132");
 	retval = platform_driver_register(&u132_platform_driver);
	if (retval)
		destroy_workqueue(workqueue);

 	return retval;
 }
 