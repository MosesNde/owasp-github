 
 	if (!n_mod || n_mod * sizeof(*sof_mod) != section.header.data.size) {
 		fprintf(stderr, "error: Invalid module manifests in '.module' section.\n");
 		return -ENOEXEC;
 	}
 
 
 		if (j == image->adsp->modules->mod_man_count) {
 			fprintf(stderr, "error: cannot find %s in manifest.\n", name);
 			return -ENOEXEC;
 		}
 	}