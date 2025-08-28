     }
 
     for (unsigned int i = 0; i < hnpCfg->linkNum; i++) {
        if (strstr(currentLink->source, "../") || strstr(currentLink->target, "../")) {
            HNP_LOGE("hnp json link source[%{public}s],target[%{public}s],does not allow the use of ../",
                 currentLink->source, currentLink->target);
             return HNP_ERRNO_INSTALLER_GET_HNP_PATH_FAILED;
         }
         HNP_LOGE("hnp install sprintf install path unsuccess.");
         return HNP_ERRNO_BASE_SPRINTF_FAILED;
     }
    if (strstr(hnpInfo->hnpVersionPath, "../")) {
        HNP_LOGE("hnp version path[%{public}s], does not allow the use of ../", hnpInfo->hnpVersionPath);
         return HNP_ERRNO_INSTALLER_GET_HNP_PATH_FAILED;
     }
 