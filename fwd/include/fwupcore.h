#ifndef FWUPCORE_H
#define FWUPCORE_H
#include "fwupcommon.h"
/* This code is exposed to end-user. */

/* Major functionality */
int scanUSBforUpdate (const char *usbDeviceName); /* scan usb drive for updates */
/*void checkForUpdates (const char *cfgFileName);*/ /* check for updates */

int checkUpdateAvailable(); /* sends device ID, gets firmware ID */

int extractFirmwareID();   /* Initiate live-update transaction */
int extractFirmwareUpdatePlanID(); /* parse response to live-update */

int fetchUpdatePlan (int updatePlanUUID); /* fetch update plan */
int checkUpdatePlanValidity(); /* check validity of update plan */
int parseUpdatePlan();     /* interpret update plan, check validity */

int fetchUpdatePackage (int updatePackageUUID); /* send packge ID, fetch packages */
int parseUpdatePackage();  /* extract manifest IDs array */

int fetchUpdateManifest (int updateManifestUUID); /* Get Manifest data */
int parseUpdateManifest(); /* Parse manifest to extract binary ID */

int fetchUpdateBinary (int updateBinaryUUID); /* using binary ID fetch binary */

int pickUpdatesToApply();  /* determine which plan updates to be applied */
int applyAppUpdate();      /* application of updates */
int applyPatchUpdate();    /* apply a patch */
int rollbackAppUpdate (const char *updtResultFile); /* rollback of updates */
int reportAppUpdateResult (const char *updtResultFile); /* report results of updates */
int storeAppUpdateState(); /* preserve state of update across reboot */

void initCore();
void finiCore();
int sendRequest (RequestID reqId);

#endif  /* FWUPCORE_H */
