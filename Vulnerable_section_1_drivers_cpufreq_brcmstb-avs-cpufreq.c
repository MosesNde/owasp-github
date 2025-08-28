 	int ret;
 
 	ret = cpufreq_unregister_driver(&brcm_avs_driver);
	if (ret)
		return ret;
 
 	brcm_avs_cpufreq_debug_exit(pdev);
 