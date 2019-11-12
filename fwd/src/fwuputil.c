#include <stdio.h>
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
 * @brief Create advisory lock.
 *
 * @param : None.
 *
 * @return : None.
 */
int createLock()
{
  lockHandle = open (LOCKFILE, O_CREAT|O_EXCL, 7000);
  return (lockHandle);
}

/**
 * @brief Remove advisory lock.
 *
 * @param : None.
 *
 * @return : None.
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
 * @brief Default signal handler.
 *
 *        Handles following signals:
 *          SIGUSR1 : USB inserted
 *          SIGUSR2 : USB ejected
 *          SIGKILL : Stops agent
 *
 * @param sig : Signal to be handled.
 *
 * @return : None.
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
 * periodically checks for availability of update
 * if update is available, calls a notifier function.
 *
 * Periodic checks have been deprecated from core library.
void dummy() { }
 */

/**
 * @brief Read pre-configured delay value for update checks.
 *
 *        Reads configrable check period from configuration file
 *        if no delay is configured, sets 24h as delay to check for updates.
 *        Delay value is to be specified in terms of clock minutes.
 *
 * @param : None.
 *
 * @return unsigned int : Delay value in Minutes.
 */
unsigned int getConfiguredDelay (const char *cfgFileName)
{
    char cfgFile[80];
    const char *name;
    unsigned int updFreq = 24 * 60;
    struct json_object_iterator itBeg, itEnd;
    struct json_object *root, *obj;

    root = json_object_from_file (cfgFileName);
    if (root == NULL)
        root = json_object_from_file (DEFAULT_CONFIG_FILE);

    itBeg = json_object_iter_begin (root);
    itEnd = json_object_iter_end (root);
    while (!json_object_iter_equal (&itBeg, &itEnd))
    {
      name = json_object_iter_peek_name (&itBeg);
      if (strcmp (name, "otaFreqMinutes") == 0)
      {
        obj = json_object_iter_peek_value (&itBeg);
        if (strcmp ("int", json_type_to_name(json_object_get_type (obj))) == 0)
          updFreq = (unsigned int) json_object_get_int (obj);
        break;
      }
      json_object_iter_next (&itBeg);
    }

    return (updFreq);
}

/* ******* USB related functionality ******* */
/**
 * @brief Utility function to search for ".fup" file(s).
 *
 *        Searches for presence of ".fup" file on a given disk.
 *
 * @param dir : Directory to search the file pattern in.
 *
 * @return int : 0 if no file found, 1 otherwise.
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

/* -------------------------------------------------------------------------- */

/* Old code, kept for reference till development phase, to be deleted later */

#if 0
/**
 * this would probably need a separate thread.
 */
void updateCheckerLoop (const char *cfgFileName)
{
  const char *fname = "/home/test/tmp/fwd/fwupdate.cfg";
  unsigned int delay = getConfiguredDelay (fname);
  printf ("configured delay = %d\n", delay);
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
