#pragma once

#define __STRINGIFY__(x)            #x
#define __EXPAND__(x)               __STRINGIFY__(x)

#define APP_NAME                    "Geen Text Tool"

#define APP_VERSION_MAJOR           0
#define	APP_VERSION_MINOR           1

#define APP_TITLE                   APP_NAME " " APP_VERSION
#define APP_VERSION                 __EXPAND__(APP_VERSION_MAJOR) "." __EXPAND__(APP_VERSION_MINOR)
#define APP_VERSION_DATE_TIME       __DATE__ " " __TIME__
