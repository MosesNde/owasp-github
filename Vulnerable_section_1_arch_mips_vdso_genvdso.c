 	if (fstat(fd, &stat) != 0) {
 		fprintf(stderr, "%s: Failed to stat '%s': %s\n", program_name,
 			path, strerror(errno));
 		return NULL;
 	}
 
 	if (addr == MAP_FAILED) {
 		fprintf(stderr, "%s: Failed to map '%s': %s\n", program_name,
 			path, strerror(errno));
 		return NULL;
 	}
 
 	if (memcmp(ehdr->e_ident, ELFMAG, SELFMAG) != 0) {
 		fprintf(stderr, "%s: '%s' is not an ELF file\n", program_name,
 			path);
 		return NULL;
 	}
 
 	default:
 		fprintf(stderr, "%s: '%s' has invalid ELF class\n",
 			program_name, path);
 		return NULL;
 	}
 
 	default:
 		fprintf(stderr, "%s: '%s' has invalid ELF data order\n",
 			program_name, path);
 		return NULL;
 	}
 
 	if (swap_uint16(ehdr->e_machine) != EM_MIPS) {
 		fprintf(stderr,
 			"%s: '%s' has invalid ELF machine (expected EM_MIPS)\n",
 			program_name, path);
 		return NULL;
 	} else if (swap_uint16(ehdr->e_type) != ET_DYN) {
 		fprintf(stderr,
 			"%s: '%s' has invalid ELF type (expected ET_DYN)\n",
 			program_name, path);
 		return NULL;
 	}
 
 	*_size = stat.st_size;
 	return addr;
 }
 
 	/* Calculate and write symbol offsets to <output file> */
 	if (!get_symbols(dbg_vdso_path, dbg_vdso)) {
 		unlink(out_path);
 		return EXIT_FAILURE;
 	}
 
 	fprintf(out_file, "};\n");
 
 	return EXIT_SUCCESS;
 }