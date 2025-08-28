 		if ((cache_flags & CACHE_FLAGS_NOAFF) && !pinned) {
 			const int current = sched_getcpu();
 
			if (current < 0)
				return EXIT_FAILURE;

 			cpu = (uint32_t)current;
 		} else {
 			static uint32_t cpu_idx = 0;
 			} else {
 				const int current = sched_getcpu();
 
				if (current < 0)
					return EXIT_FAILURE;

 				cpu = (uint32_t)current;
 			}
 		}
 		stress_metrics_set(args, j, metrics_description[j],
 			rate, STRESS_METRIC_HARMONIC_MEAN);
 	}
 #if defined(HAVE_SCHED_GETAFFINITY) &&	\
     defined(HAVE_SCHED_GETCPU)
 	stress_free_usable_cpus(&cpus);