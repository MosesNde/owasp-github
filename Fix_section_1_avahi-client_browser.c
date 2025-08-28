         if (avahi_normalize_name(buf, domain, sizeof(domain)))
             b->static_browse_domains = avahi_string_list_add(b->static_browse_domains, domain);
     }

    fclose(f);
 }
 
 static void domain_browser_ref(AvahiDomainBrowser *db) {