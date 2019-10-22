#include <stdio.h>
#include <strings.h>  /* bzero */

int main (void)
{
  const char *resultFile = "/home/test/tmp/fw_sandbox/fwsim/fwbackup/result";
  const char *rollbackScript = "/home/test/tmp/fwd/scripts/rollback_app_update.sh";
  FILE *fp;
  int status, tval;
  char dirStr[18];
  char rollbackCmd [180];

  bzero (&rollbackCmd[0], 180);
  bzero (&dirStr[0], 18);
  fp = fopen (resultFile, "r");
  fscanf (fp, "%d:%d", &status, &tval);
  fscanf (fp, "%s", &dirStr[0]);
  fclose (fp);

  printf ("status = %d, timestamp = %d, dir = %s\n", status, tval, dirStr);
  printf ("%s\n", rollbackScript);
  printf ("%s\n", dirStr);

  sprintf (rollbackCmd, "%s %s", rollbackScript, dirStr);
  printf ("%s\n", rollbackCmd);

  return (0);
}
