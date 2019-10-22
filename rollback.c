#include <stdio.h>

int main (void)
{
  const char *resultFile = "/home/test/tmp/fw_sandbox/fwsim/fwbackup/result";
  FILE *fp;
  int status, tval;
  char dirStr[15];

  fp = fopen (resultFile, "r");
  fscanf (fp, "%d:%d", &status, &tval);
  fscanf (fp, "%s", &dirStr[0]);

  printf ("status = %d, timestamp = %d, dir = %s\n", status, tval, dirStr);

  return (0);
}
