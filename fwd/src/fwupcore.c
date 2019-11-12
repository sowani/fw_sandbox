#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include "fwuputil.h"
#include "fwupcore.h"
#include "json.h"

/* ******* core init/fini functionality ******* */
/**
 * @brief Initialise library code.
 *
 *        Library initialisation code.
 *        Declare and initialise signal handler.
 *
 * @param : None.
 *
 * @return : None.
 */
void initCore (void)
{
  /* if, for some reason, old lock exists, remove it. */
  removeLock();

  /**
   * Signal usage:
   * SIGUSR1 : USB inserted
   * SIGUSR2 : USB removed
   * SIGKILL : stop and exit OTA process
   */
  signal (SIGUSR1, signalCB);
  signal (SIGUSR2, signalCB);
  signal (SIGKILL, signalCB);

  /* initialise global variables */
  usbDetected = 0;
  loopOver = 1;
  fwUpdateState.updateStatus = UPDATE_NOT_CHECKED;
  fwUpdateState.updateTime = time(NULL);
  DEBUG_PRINT (("initCore completed.\n"));
}

/**
 * @brief Library clean up code.
 *
 * @param : None.
 *
 * @return : None.
 */
void finiCore (void)
{
  removeLock();
  DEBUG_PRINT (("finiCore completed.\n"));
}

/**
 * @brief REST request sender.
 *
 *        Send REST command to update server and receive response.
 *        TBD: how to handle response buffer (return as char *, send
 *             as an argument)
 *
 * @param reqId : Request ID to be sent.
 *
 * @return int : Status of request sent.
 */
int sendRequest (RequestID reqId)
{
  int retVal = 0;
  char getCmdStr [MAX_GETCMD_LEN];

  /* Form REST command string */
  /* TODO: Once request details are finalized, i.e. parameters to be
   *       sent in body of the command, those also need to be added to
   *       the following command construction code.
   */
  switch (reqId)
  {
    case GET_FIRMWARE:
      sprintf (getCmdStr, "GET /firmware HTTP/1.1\n");
      break;
    case GET_FIRMWARE_UPDATEPLAN:
      sprintf (getCmdStr, "GET /firmware-updateplan HTTP/1.1\n");
      break;
    case GET_FIRMWARE_PACKAGE:
      sprintf (getCmdStr, "GET /firmware-package HTTP/1.1\n");
      break;
    case GET_FIRMWARE_MANIFEST:
      sprintf (getCmdStr, "GET /firmware-manifest HTTP/1.1\n");
      break;
    case GET_FIRMWARE_BINARY:
      sprintf (getCmdStr, "GET /firmware-binary HTTP/1.1\n");
      break;
    case GET_DEPLOYMENT:
      sprintf (getCmdStr, "GET /firmware HTTP/1.1\n");
      break;
    case GET_LIVE_DEPLOYMENT:
      sprintf (getCmdStr, "GET /live-deployment HTTP/1.1\n");
      break;
    default:
      printf ("Invalid command received.\n");
      break;
  }

  /* TODO: Open connection with update server and send the command */
  printf ("%s", getCmdStr);

  /* TODO: Read response and save it for later processing */
  return (retVal);
}
/* ******* core init/fini functionality ******* */

/* ******* USB related functionality ******* */
/**
 * @brief Scan given USB device for updates.
 *
 *        Updates reside in either "/" or in "/FirmwareUpdates"
 *
 * @param usbDeviceName : Name of USB device.
 *
 * @return int
   -1 : Error scanning for update,
    0 : No update available,
   >0 : update available
 */
int scanUSBforUpdate (const char *usbDeviceName)
{
  FILE *fp;
  struct dirent **namelist;
  int n, result;
  char usbDev [MAX_USBDEVNAME_LEN], dirname [MAX_DIRNAME_LEN];

  DEBUG_PRINT (("in scanUSBforUpdate.\n"));
  bzero (&usbDev[0], MAX_USBDEVNAME_LEN);

  /* if no device name is provided, use default */
  if (strlen (usbDeviceName) > 0)
    strncpy (usbDev, usbDeviceName, strlen (usbDeviceName));
  else
    strncpy (usbDev, DEFAULT_USB_DEVICE, strlen (DEFAULT_USB_DEVICE));
  n = strlen (usbDev);

  fp = fopen (usbDev, "r");
  if (fp == NULL)
    return -1;

  DEBUG_PRINT (("searching for update files\n"));
  /* search update directories for ".fup" files */
  strncpy (dirname, usbDev, n);
  strncpy (dirname+n, "/FirmwareUpdates", strlen ("/FirmwareUpdates"));

  result = scandir (dirname, &namelist, fupFilter, alphasort);

  /* In case no .fup is present in /FirmwareUpdates, search in "/". */
  if (result <= 0)
  {
    sprintf (dirname, "%s", usbDev);
    result = scandir (dirname, &namelist, fupFilter, alphasort);
  }
  DEBUG_PRINT (("scanUSBforUpdate completed.\n"));
  return (result);
}
/* ******* USB related functionality ******* */

/* ******* Update availability related functionality ******* */
/**
 * @brief Check if any updates are available.
 *
 *        This function will make calls to:
 *          GET /live-deployment and
 *          GET /firmware.
 *
 * @param : None
 *
 * @return int: 0 if no updates available, 1 if available.
 */
int checkUpdateAvailable()
{
  int retVal = 1;
  DEBUG_PRINT (("Checking if update available.\n"));
  retVal = sendRequest (GET_LIVE_DEPLOYMENT);
  retVal = sendRequest (GET_FIRMWARE);

  /* TODO: parse response and check if update is available */
  /* if update available */
    retVal = 1;
  /* else */
    retVal = 0;
  fwUpdateState.updateStatus = UPDATE_AVAILABLE;
  fwUpdateState.updateTime = time(NULL);
  return (retVal);
}
/* ******* Update availability related functionality ******* */

/* ******* Update download and inspection related functionality ******* */
/**
 * @brief Fetches update plan from update server.
 *
 * @param updatePlanUUID : UUID of update plan.
 *
 * @return int : 0 on success, error code otherwise.
 */
int fetchUpdatePlan (int updatePlanUUID)
{
  int retVal = 0;
  retVal = sendRequest (GET_FIRMWARE_UPDATEPLAN);
  return (retVal);
}

int checkUpdatePlanValidity()
{}

int parseUpdatePlan()
{}

int pickUpdatesToApply()
{}

/**
 * @brief Fetches update manifest file from update server.
 *
 * @param updateManifestUUID : UUID of update manifest.
 *
 * @return int : 0 on success, error code otherwise.
 */
int fetchUpdateManifest (int updateManifestUUID)
{
  int retVal = 0;
  retVal = sendRequest (GET_FIRMWARE_MANIFEST);
  return (retVal);
}

int parseUpdateManifest()
{}

/**
 * @brief Fetches update package from update server.
 *
 * @param updatePackageUUID : UUID of update package.
 *
 * @return int : 0 on success, error code otherwise.
 */
int fetchUpdatePackage (int updatePackageUUID)
{
  int retVal = 0;
  retVal = sendRequest (GET_FIRMWARE_PACKAGE);
  return (retVal);
}

int parseUpdatePackage()
{}

/**
 * @brief Fetches update binary from update server.
 *
 * @param updateBinaryUUID : UUID of update binary.
 *
 * @return int : 0 on success, error code otherwise.
 */
int fetchUpdateBinary (int updateBinaryUUID)
{
  int retVal = 0;
  retVal = sendRequest (GET_FIRMWARE_BINARY);
  return (retVal);
}
/* ******* Update download and inspection related functionality ******* */

/* ******* apply/rollback update and report result ******* */
/**
 * @brief Apply application updates.
 *
 * @param None.
 *
 * @return int : 0 on success, 1 on failure.
 */
int applyAppUpdate()
{
  int retVal = 1;
  retVal = createLock();
  retVal = system ("scripts/apply_app_update.sh");
  removeLock();
  fwUpdateState.updateStatus = UPDATE_SUCCESSFUL;
  fwUpdateState.updateTime = time(NULL);
  return (retVal);
}

/**
 * @brief Apply application patch updates.
 *
 * @param None.
 *
 * @return int : 0 on success, 1 on failure.
 */
int applyPatchUpdate()
{
  int retVal = 1;
  retVal = createLock();
  retVal = system ("scripts/apply_app_patch.sh");
  removeLock();
  fwUpdateState.updateStatus = UPDATE_SUCCESSFUL;
  fwUpdateState.updateTime = time(NULL);
  return (retVal);
}

/**
 * @brief Rollback latest update.
 *
 * @param updtResultFile : Name and location of update results file.
 *
 * @return int : 0 on success, 1 on failure.
 */
int rollbackAppUpdate (const char *updtResultFile)
{
  FILE *fp;
  int status, tval, retVal = 0;
  char dirStr [MAX_DIRSTR_LEN], rollbackCmd [MAX_RBCMD_LEN];

  fp = fopen (updtResultFile, "r");
  if (fp == NULL)
    return -1;

  fscanf (fp, "%d:%d", &status, &tval); /* not used at present */
  fscanf (fp, "%s", &dirStr[0]);
  fclose (fp);
  sprintf (rollbackCmd, "%s %s", "scripts/rollback_app_update.sh", dirStr);
  printf ("rollback Cmd = %s\n", rollbackCmd);
  retVal = createLock();
  retVal = system (rollbackCmd);
  removeLock();

  /* Update status with rollback state */
  fwUpdateState.updateStatus = UPDATE_ROLLEDBACK;
  fwUpdateState.updateTime = time(NULL);
  return (retVal);
}

/**
 * @brief Sends app update result to update server.
 *
 * @param updtResultFile : Name and location of update results file.
 *
 * @return int : App update result.
 */
int reportAppUpdateResult (const char *updtResultFile)
{
  FILE *fp;
  int status, tval;

  fp = fopen (updtResultFile, "r");
  if (fp == NULL)
    return -1;

  fscanf (fp, "%d:%d", &status, &tval); /* tval not used at present */
  fclose (fp);
  return (status);
}

/**
 * @brief Saves app-firmware update status details to persistent storage
 *
 *        Stores application firmware update status to permanent storage
 *        using JSON format.
 *
 * @param shResultFile : Name and location of result file created by update.
 *
 * @return int : 0 on success, 1 on failure.
 */
int storeAppUpdateState (const char *shResultFile)
{
  const char *outputFile = "sample.json";
  /* This is temporary, shResultFile should be utilised instead. */
  /* const char *fname = "/home/test/tmp/fw_sandbox/fwsim/fwbackup/result"; */

  int retval, val, ts;
  struct json_object *obj, *intObj1, *intObj2;
  FILE *fp;

  retval = val = ts = 0;
  fp = fopen (shResultFile, "r");
  if (fp == NULL)
    return -1;

  fscanf (fp, "%d:%d", &val, &ts);
  fclose (fp);

  /* construct sample JSON */
  obj = json_object_new_object();

  intObj1 = json_object_new_int (val);
  retval  = json_object_object_add (obj, "updateState", intObj1);
  intObj2 = json_object_new_int (ts);
  retval  = json_object_object_add (obj, "updateTime", intObj2);

  /* export sample JSON to file */
  retval = json_object_to_file_ext (outputFile, obj, JSON_C_TO_STRING_PRETTY);
  return (retval);
}
/* ******* apply/rollback update and report result ******* */

/* -------------------------------------------------------------------------- */
/* Old code, to be deleted */
#if 0
void startPeriodicUpdateChecker (const char *cfgFileName)
{
  /* this would probably need a separate thread. */
  int n;
  unsigned int delay = getConfiguredDelay (cfgFileName);
  printf ("configured delay = %d\n", delay);
  n = checkUpdateAvailable();
  printf ("update available = %d\n", n);

  while (1)
  {
    if (loopOver == 0)
      break;

    if (checkUpdateAvailable())
    {
      if (fetchUpdatePlan() != 0)
      {
        printf ("OTA agent unable to download updates.\n");
      }
    }

    sleep (delay);
  }
}
#endif
/* -------------------------------------------------------------------------- */
