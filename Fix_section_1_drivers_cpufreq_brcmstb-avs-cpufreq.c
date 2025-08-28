 	int ret;
 
 	ret = cpufreq_unregister_driver(&brcm_avs_driver);
	WARN_ON(ret);
 
 	brcm_avs_cpufreq_debug_exit(pdev);
 