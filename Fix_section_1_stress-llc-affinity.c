 	if (llc_size == 0) {
 		pr_inf_skip("%s: cannot determine cache details, skipping stressor\n",
 			args->name);
		stress_free_usable_cpus(&cpus);
 		return EXIT_NO_RESOURCE;
 	}
         llc_size *= numa_nodes;
 		MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
 	if (buf == MAP_FAILED) {
 		pr_fail("%s: mmap'd region of %zu bytes failed\n", args->name, mmap_sz);
		stress_free_usable_cpus(&cpus);
 		return EXIT_NO_RESOURCE;
 	}
 	stress_set_vma_anon_name(buf, mmap_sz, "llc-buffer");