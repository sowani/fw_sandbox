#ifndef UPDATE_CORE_H
#define UPDATE_CORE_H

#include <dirent.h>

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

#define DEFAULT_UPSTREAM_CONFIG_FILE "UpstreamConfig.json"
#define DEFAULT_USB_DEVICE "/dev/sba1"
/*
#define DEFAULT_UPDATE_SOURCE_LOCATION "/tmp/fwupdate"
#define DEFAULT_BACKUP_LOCATION "/tmp/fwbackup"
*/
#define LOCKFILE "/tmp/lock-file"

#define DEBUG_PRINT(x) if (debug) printf ("DEBUG: %s", x)
#define debug 1

typedef enum updateState
{
  UPDATE_AVAILABLE = 0,
  UPDATE_DOWNLOADED,
  UPDATE_VALID,
  UPDATE_APPLIED,
  UPDATE_SUCCESSFUL,
  UPDATE_ROLLEDBACK,
  UPDATE_STATES
} updateState;

/*
typedef enum reqID
{
  FIRMWARE = 0,
  FIRMWARE_UPDATEPLAN,
  FIRMWARE_PACKAGE,
  FIRMWARE_MANIFEST,
  FIRMWARE_BINARY,
  DEPLOYMENT,
  LIVE_DEPLOYMENT,
  MAX_REQID
} RequestID;
*/

enum rollbackPolicy
{
  ROLLBACK_ALL = 0,
  ROLLBACK_AND_CONTINUE,
  CONTINUE,
  MAX_ROLLBACK_POLICIES
};

static int usbDetected = 0;
static int lockHandle;
static int loopOver = 1;

#if 0
/* Major functionality */
int checkUpdateAvailable();    /* periodic checking for updates */
int scanUSBforUpdate (const char *usbDeviceName); /* scan usb drives for updates */
int fetchUpdatePlan();         /* POST, GET */
int checkUpdatePlanValidity(); /* check validity of update plan */
int parseUpdatePlan();         /* interpret update plan, check validity */
int pickUpdatesToApply();      /* determine which plan updates to be applied */

int fetchUpdateManifest();     /* POST, GET */
int parseUpdateManifest();
int fetchUpdatePackage();      /* POST, GET fetch packages */
int parseUpdatePackage();
int fetchUpdateBinary();

int applyAppUpdate();          /* application of updates */
int rollbackAppUpdate();       /* rollback of updates */
int reportAppUpdateResult();   /* report results of updates */
int storeAppUpdateState();     /* preserve state of update across reboot */

void initCore();
void finiCore();
int sendRequest (RequestID reqId);
#endif

/* Utility functions */
void signalCB (int sig);
int createLock();
void removeLock();
unsigned int getConfiguredDelay();
int fupFilter (const struct dirent *dir);
int createFileBackup();
int checkUpdateStatus();
#endif  /* UPDATE_CORE_H */
