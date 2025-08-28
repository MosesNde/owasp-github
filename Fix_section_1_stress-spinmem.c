 		pr_inf_skip("%s: could not mmap a page of "
 			"%zu bytes, skipping stressor\n",
 			args->name, args->page_size);
		rc = EXIT_NO_RESOURCE;
		goto tidy_cpus;
 	}
 	stress_set_vma_anon_name(mapping, args->page_size, "spinmem-data");
 
                 rate * STRESS_DBL_NANOSECOND, STRESS_METRIC_HARMONIC_MEAN);
 
 	(void)munmap((void *)mapping, args->page_size);
tidy_cpus:
 #if defined(HAVE_SCHED_SETAFFINITY)
 	stress_free_usable_cpus(&cpus);
 #endif