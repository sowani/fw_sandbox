#ifndef FWUPUTIL_H
#define FWUPUTIL_H
/* This code is not exposed to end-user. */

#include <dirent.h>
#include "fwupcommon.h"

/*
 * Functionality:
 * periodic checking for updates
 * scanning usb drives for updates
 * checking validity of the update plan
 * interpreting the update plan
 * determining which updates in the plan, if any, should be applied
 * fetching packages
 * co-ordinating application of the updates
 * co-ordinating validation of the updates
 * co-ordinating rollback of the updates (if required)
 * reporting results of the updates
 * preserving state of the update across reboots
 */

#define DEFAULT_UPDATE_SOURCE_LOCATION "/tmp/fwupdate"
#define DEFAULT_BACKUP_LOCATION        "/tmp/fwbackup"
#define DEFAULT_CONFIG_FILE            "UpstreamConfig.json"
#define DEFAULT_USB_DEVICE             "/dev/sba1"
#define LOCKFILE                       "/tmp/lock-file"

/* TODO: replace with klog calls */
#ifdef DEBUG
#define DEBUG_PRINT(x) { printf ("DEBUG: "); printf x; }
#else
#define DEBUG_PRINT(x)
#endif

/* Library-wide global variables */
static int usbDetected = 0;
static int loopOver = 1;
static int lockHandle;

/* Utility functions */
void signalCB (int sig);
int createLock();
void removeLock();
unsigned int getConfiguredDelay (const char *cfgFileName);
int fupFilter (const struct dirent *dir);
int createFileBackup();

#endif  /* FWUPUTIL_H */
