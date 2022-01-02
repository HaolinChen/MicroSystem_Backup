#ifndef __CNN_SSD_H__
#define __CNN_SSD_H__

#ifdef __EMUL__
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/param.h>
#include <string.h>
#include "helpers/helpers.h"
#endif

extern AT_HYPERFLASH_FS_EXT_ADDR_TYPE cnn_ssd_L3_Flash;

#endif