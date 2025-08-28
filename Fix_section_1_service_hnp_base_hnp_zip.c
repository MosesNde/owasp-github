             unzClose(zipFile);
             return HNP_ERRNO_BASE_UNZIP_GET_INFO_FAILED;
         }
        if (strstr(fileName, "..")) {
            HNP_LOGE("unzip filename[%{public}s],does not allow the use of ..", fileName);
             unzClose(zipFile);
             return HNP_ERRNO_BASE_UNZIP_GET_INFO_FAILED;
         }