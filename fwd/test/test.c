#include <stdio.h>
#include "fwupcore.h"

int main (void)
{
  int n;
  const char *cfgFileName = "/home/test/tmp/json_sandbox/test_jsons/fwupdate.cfg";

  initCore();
  n = scanUSBforUpdate ("/home/test/tmp/fw_sandbox/fwsim/dummyUSB");
  printf ("scanUSBforUpdate returned %d\n", n);

  /* startPeriodicUpdateChecker (cfgFileName); */
  n = checkUpdateAvailable();
  if (fwUpdateState.updateStatus == UPDATE_AVAILABLE)
  {
    printf ("update time = %ld\n", fwUpdateState.updateTime);
    sendRequest (GET_FIRMWARE_MANIFEST);
    n = applyAppUpdate();
    printf ("applyAppUpdate returned %d.\n", n);
  }
  n = storeAppUpdateState ("/home/test/tmp/fw_sandbox/fwsim/fwbackup/result");
  n = reportAppUpdateResult ("/home/test/tmp/fw_sandbox/fwsim/fwbackup/result");
  printf ("result = %d\n", n);

  if (n != 0)
  {
    printf ("mock rollback ...\n");
    n = rollbackAppUpdate ("/home/test/tmp/fw_sandbox/fwsim/fwbackup/result");
  }

  finiCore();
  return (0);
}
