#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include "fwupdate.h"
#include "core.h"

/* ******* core init/fini functionality ******* */
/**
 * @brief Create advisory lock.
 *
 * @param - None.
 *
 * @return - None.
 */
int createLock()
{
  lockHandle = open (LOCKFILE, O_CREAT|O_EXCL, 7000);
  return (lockHandle);
}

/**
 * @brief Remove advisory lock.
 *
 * @param - None.
 *
 * @return - None.
 */
void removeLock()
{
  struct stat buff;
  if (0 == stat (LOCKFILE, &buff))
  {
    close (lockHandle);
    remove (LOCKFILE);
  }
}

/**
 * @brief Initialise library code.
 *
 *        Library initialisation code.
 *        Declare and initialise signal handler.
 *
 * @param - None.
 *
 * @return - None.
 */
//void initCore (void)
//{
  /* if, for some reason, old lock exists, remove it. */
  //removeLock();
  //signal (SIGUSR1, signalCB);
  //signal (SIGUSR2, signalCB);
  //signal (SIGKILL, signalCB);

  /* initialise global variables */
  //usbDetected = 0;
  //loopOver = 1;
  //DEBUG_PRINT ("initCore completed.\n");
//}

/**
 * @brief Library clean up code.
 *
 * @param - None.
 *
 * @return - None.
 */
//void finiCore (void)
//{
  //removeLock();
  //DEBUG_PRINT ("finiCore completed.\n");
//}

/**
 * @brief Default signal handler.
 *
 * Handles following signals:
 *   SIGUSR1 : USB inserted
 *   SIGUSR2 : USB ejected
 *   SIGKILL : Stops agent
 *
 * @param sig - Signal to be handled.
 *
 * @return - None.
 */
void signalCB (int sig)
{
    if (sig == SIGUSR1)
    {
        /* USB insertion event detected. */
        usbDetected = 1;
    } else if (sig == SIGUSR2)
    {
        /* USB removal event detected. */
        usbDetected = 0;
    } else if (sig == SIGKILL)
    {
        //stopService();
    }
}

/**
 * @brief REST request sender.
 *
 *        Send REST command to update server and receive response.
 *        TBD: how to handle response buffer (return as char *, send as an argument)
 *
 * @param reqId - Request ID to be sent.
 *
 * @return int - Status of request sent.
 */
//int sendRequest (RequestID reqId)
//{
  //int retVal = 0;
  //switch (reqId)
  //{
    //case FIRMWARE:
      //printf ("GET /firmware\n");
      //break;
    //case FIRMWARE_UPDATEPLAN:
      //printf ("GET /firmware-updateplan\n");
      //break;
    //case FIRMWARE_PACKAGE:
      //printf ("GET /firmware-package\n");
      //break;
    //case FIRMWARE_MANIFEST:
      //printf ("GET /firmware-manifest\n");
      //break;
    //case FIRMWARE_BINARY:
      //printf ("GET /firmware-binary\n");
      //break;
    //case DEPLOYMENT:
      //printf ("GET /firmware\n");
      //break;
    //case LIVE_DEPLOYMENT:
      //printf ("GET /live-deployment\n");
      //break;
    //default:
      //break;
  //}
  //return (retVal);
//}

/**
 * periodically checks for availability of update
 * if update is available, calls a notifier function
 */
void dummy()
{
}

/**
 * @brief Read pre-configured delay value for update checks.
 *
 *        Reads configrable check period from configuration file
 *        if no delay is configured, sets 24h as delay to check for updates.
 *        Delay value is to be specified in terms of clock minutes.
 *
 * @param - None.
 *
 * @return unsigned int - Delay value in Minutes.
 */
unsigned int getConfiguredDelay()
{
    /*json cfgRoot;*/
    char cfgFile[80];
    unsigned int updFreq = 1;

    /*
     * Parse JSON from configuration file: logic TBD
     * if not given in config file, use default
     * TODO: convert from C++ to C.
     */
    /*
    ifstream cfgFile;
    if (userCfgFile)
      strcpy (cfgFile, userCfgFileName);
    else
      strcpy (cfgFile, DEFAULT_UPSTREAM_CONFIG_FILE);

    cfgFile.open (cfgFile);
    if (cfgFile) {
        cfgFile >> cfgRoot;
        cfgFile.close();
    }

    if (cfgRoot.count("otaFreqMinutes") != 0)
        updFreq = cfgRoot["otaFreqMinutes"];
    else
        updFreq = 24 * 60;
    */

    return (updFreq);
}

/* ******* USB related functionality ******* */

/**
 * @brief Utility function to search for ".fup" file(s).
 *
 *        Searches for presence of ".fup" file on a given disk.
 *
 * @param dir - Directory to search the file pattern in.
 *
 * @return int - 0 if no file found, 1 otherwise.
 */
int fupFilter (const struct dirent *dir)
{
  int len = 0;
  const char *dname = dir->d_name;
  int extnLen = strlen (".fup");
  len = strlen (dname) - extnLen;  /* ".fup" */
  if (len > 0)
  {
    if (strncmp (dname + len, ".fup", extnLen) == 0)
      return 1;
  }
  return 0;
}

/**
 * @brief Scan given USB device for updates.
 *
 *        Updates reside in either "/" or in "/FirmwareUpdates"
 *
 * @param usbDeviceName - Name of USB device.
 *
 * @return int
   -1 : Error scanning for update,
    0 : No update available,
   >0 : update available
 */
//int scanUSBforUpdate (const char *usbDeviceName)
//{
  //FILE *fp;
  //struct dirent **namelist;
  //int n, result;
  //char usbDev[60], dirname[80];

  //DEBUG_PRINT ("in scanUSBforUpdate.\n");
  //bzero (&usbDev[0], 50);

  /* if no device name is provided, use default */
  //if (strlen (usbDeviceName) > 0)
    //strncpy (usbDev, usbDeviceName, strlen (usbDeviceName));
  //else
    //strncpy (usbDev, DEFAULT_USB_DEVICE, strlen (DEFAULT_USB_DEVICE));
  //n = strlen (usbDev);

  //fp = fopen (usbDev, "r");
  //if (fp == NULL)
    //return -1;

  //DEBUG_PRINT ("searching for update files\n");
  /* search update directories for ".fup" files */
  //strncpy (dirname, usbDev, n);
  //strncpy (dirname+n, "/FirmwareUpdates", strlen ("/FirmwareUpdates"));

  //result = scandir (dirname, &namelist, fupFilter, alphasort);

  /* In case no .fup is present in /FirmwareUpdates, search in "/" */
  //if (result <= 0)
  //{
    //sprintf (dirname, "%s", usbDev);
    //result = scandir (dirname, &namelist, fupFilter, alphasort);
  //}
  //DEBUG_PRINT ("scanUSBforUpdate completed.\n");
  //return (result);
//}

/* ******* Update availability related functionality ******* */

/**
 * This function will make calls to:
 *   GET /live-deployment and
 *   GET /firmware.
 *
 * @return int: 0 if no updates available, 1 if available.
 */
//int checkUpdateAvailable()
//{
  //int retVal = 1;
  //DEBUG_PRINT ("Checking if update available.\n");
  //sendRequest (LIVE_DEPLOYMENT);
  //sendRequest (FIRMWARE);
  //return (retVal);
//}

/**
 * this would probably need a separate thread.
 */
void updateCheckerLoop()
{
  unsigned int delay = getConfiguredDelay();
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

/* ******* Update download and inspection related functionality ******* */
//int fetchUpdatePlan()
//{
  //sendRequest (FIRMWARE_UPDATEPLAN);
//}

//int checkUpdatePlanValidity()
//{}

//int parseUpdatePlan()
//{}

//int pickUpdatesToApply()
//{}

//int fetchUpdateManifest()
//{
  //sendRequest (FIRMWARE_MANIFEST);
//}

//int parseUpdateManifest()
//{}

//int fetchUpdatePackage()
//{
  //sendRequest (FIRMWARE_PACKAGE);
//}

//int parseUpdatePackage()
//{}

//int fetchUpdateBinary()
//{
  //sendRequest (FIRMWARE_BINARY);
//}

/* ******* apply/rollback update and report result ******* */
//int applyAppUpdate()
//{
  //return (system ("update.sh"));
//}

//int rollbackAppUpdate()
//{}

//int reportAppUpdateResult()
//{}

//int storeAppUpdateState()
//{}
