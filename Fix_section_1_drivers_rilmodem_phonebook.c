 	g_tree_insert(ref->phonebook, GINT_TO_POINTER(adn_idx), new_entry);
 
 	if (extension_record != UNUSED) {
		const struct pb_file_info *f_info = ext1_info(ref->pb_files);
		if (f_info == NULL)
			return new_entry;

 		struct record_to_read *ext_rec =
 			g_try_malloc0(sizeof(*ext_rec));
		if (ext_rec == NULL)
			return new_entry;
 
 		if (ext_rec && f_info) {
 			ext_rec->file_id = f_info->file_id;
 	g_tree_insert(ref->phonebook, GINT_TO_POINTER(fdn_idx), new_entry);
 
 	if (extension_record != UNUSED) {
		const struct pb_file_info *f_info = ext2_info(ref->pb_files);
		if (f_info == NULL)
			return new_entry;

 		struct record_to_read *ext_rec =
 			g_try_malloc0(sizeof(*ext_rec));
		if (ext_rec == NULL)
			return new_entry;
 
 		if (ext_rec && f_info) {
 			ext_rec->file_id = f_info->file_id;
 	DBG("extension_record %d aas %d", extension_record, aas_record);
 
 	if (extension_record != UNUSED) {
		const struct pb_file_info *f_info = ext1_info(ref->pb_files);
		if (f_info == NULL)
			return;

 		struct record_to_read *ext_rec =
 			g_try_malloc0(sizeof(*ext_rec));
		if (ext_rec == NULL)
			return;
 
 		if (ext_rec && f_info) {
 			ext_rec->file_id = f_info->file_id;
 	/* Check if there is more extension data */
 	next_extension_record = msg[12];
 	if (next_extension_record != UNUSED) {
		const struct pb_file_info *f_info = ext1_info(ref->pb_files);
		if (f_info == NULL)
			return;

 		struct record_to_read *ext_rec =
 			g_try_malloc0(sizeof(*ext_rec));
		if (ext_rec == NULL)
			return;
 
 		if (ext_rec && f_info) {
 			DBG("next_extension_record %d", next_extension_record);
 	/* Check if there is more extension data */
 	next_extension_record = msg[12];
 	if (next_extension_record != UNUSED) {
		const struct pb_file_info *f_info = ext2_info(ref->pb_files);
		if (f_info == NULL)
			return;

 		struct record_to_read *ext_rec =
 			g_try_malloc0(sizeof(*ext_rec));
		if (ext_rec == NULL)
			return;
 
 		if (ext_rec && f_info) {
 			DBG("next_extension_record %d", next_extension_record);
 	}
 
 	ref_rec->phonebook = g_tree_new(comp_int);
	if (ref_rec->phonebook == NULL) {
		ofono_error("%s: OOM", __func__);
		g_free(ref_rec);
		export_and_return(FALSE, cbd);
		return;
	}
 
 	/* Only EF_ADN and EF_EXT1 read for SIM */
 
 	f_info = g_try_malloc0(sizeof(*f_info));
 	if (f_info == NULL) {
 		ofono_error("%s: OOM", __func__);
		g_tree_destroy(ref_rec->phonebook);
		g_free(ref_rec);
 		export_and_return(FALSE, cbd);
 		return;
 	}
 	f_ext1 = g_try_malloc0(sizeof(*f_ext1));
 	if (f_ext1 == NULL) {
 		ofono_error("%s: OOM", __func__);
		g_tree_destroy(ref_rec->phonebook);
		g_free(ref_rec);
		g_free(f_info);
 		export_and_return(FALSE, cbd);
 		return;
 	}
 	}
 
 	ref_rec->phonebook = g_tree_new(comp_int);
	if (ref_rec->phonebook == NULL) {
		ofono_error("%s: OOM", __func__);
		g_free(ref_rec);
		fdn_export_and_return(FALSE, cbd);
		return;
	}
 
 	/* Only EF_FDN and EF_EXT2 read for USIM */
 
 	f_fdn = g_try_malloc0(sizeof(*f_fdn));
 	if (f_fdn == NULL) {
 		ofono_error("%s: OOM", __func__);
		g_tree_destroy(ref_rec->phonebook);
		g_free(ref_rec);
 		fdn_export_and_return(FALSE, cbd);
 		return;
 	}
 	f_ext2 = g_try_malloc0(sizeof(*f_ext2));
 	if (f_ext2 == NULL) {
 		ofono_error("%s: OOM", __func__);
		g_tree_destroy(ref_rec->phonebook);
		g_free(ref_rec);
		g_free(f_fdn);
 		fdn_export_and_return(FALSE, cbd);
 		return;
 	}
 				ofono_phonebook_update_cb_t cb, void *data)
 {
 	struct pb_data *pbd = ofono_phonebook_get_data(pb);
	struct ofono_phone_number phone_number;
 	int rec_len, file_len, rec_count;
 	unsigned char effdn[255];
 	struct cb_data *cbd;
 
 	cbd = cb_data_new(cb, data, pb);
 
	string_to_phone_number(new_number, &phone_number);
 
	sim_adn_build(effdn, rec_len, &phone_number, identifier);
 
 	ofono_sim_write(pbd->sim_context, SIM_EFFDN_FILEID,
 			fdn_update_cb, OFONO_SIM_FILE_STRUCTURE_FIXED,