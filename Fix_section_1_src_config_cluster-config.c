                 if (!strcmp(child[j]->element, haproxy_disabled)) {
                     if (strcmp(child[j]->content, "yes") && strcmp(child[j]->content, "no")) {
                         merror("Detected an invalid value for the disabled tag '%s'. Valid values are 'yes' and 'no'.", child[j]->element);
                        OS_ClearNode(child);
                         return OS_INVALID;
                     }
                 } else if (!strcmp(child[j]->element, frequency)) {
                 } else if (!strcmp(child[j]->element, haproxy_address)) {
                     if (!strlen(node[i]->content)) {
                         merror("HAProxy address is missing in the configuration");
                        OS_ClearNode(child);
                         return OS_INVALID;
                     }
                 } else if (!strcmp(child[j]->element, haproxy_port)) {
                 } else if (!strcmp(child[j]->element, haproxy_protocol)) {
                     if (strcmp(child[j]->content, "http") && strcmp(child[j]->content, "https")) {
                         merror("Detected an invalid value for the haproxy_protocol tag '%s'. Valid values are 'http' and 'https'.", child[j]->element);
                        OS_ClearNode(child);
                         return OS_INVALID;
                     }
                 } else if (!strcmp(child[j]->element, haproxy_user)) {
                     if (!strlen(node[i]->content)) {
                         merror("HAProxy user is missing in the configuration");
                        OS_ClearNode(child);
                         return OS_INVALID;
                     }
                 } else if (!strcmp(child[j]->element, haproxy_password)) {
                     if (!strlen(node[i]->content)) {
                         merror("HAProxy password is missing in the configuration");
                        OS_ClearNode(child);
                         return OS_INVALID;
                     }
                 } else if (!strcmp(child[j]->element, haproxy_backend)) {