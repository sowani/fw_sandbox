#include <dirent.h>
#include <stdio.h>
#include <string.h>

/**
 * Scan given USB device for updates.
 * Updates reside in either "/" or in "/FirmwareUpdates"
 */
int fupFilter (const struct dirent *dir)
{
  int len = 0;
  const char *dname = dir->d_name;
  len = strlen (dname) - 4;  /* ".fup" */
  if (len > 0)
  {
    if (strncmp (dname + len, ".fup", 4) == 0)
      return 1;
  }
  return 0;
}

int scanUSBforUpdate (const char *usbDeviceName)
{
  FILE *fp;
  struct dirent **namelist;
  int n;

  fp = fopen (usbDeviceName, "r");
  if (fp == NULL)
  {
    printf ("%s unavailable.\n", usbDeviceName);
    return -1;
  }

  /* check for update directories for ".fup" files */
  n = scandir (usbDeviceName, &namelist, fupFilter, alphasort);
  printf ("n = %d\n", n);
  if (n >= 0)
  {
    int cnt;
    for (cnt = 0; cnt < n; cnt++)
      puts (namelist[cnt]->d_name);
  }
  if (n == -1)
    printf ("error\n");
  return 0;
}

int main (void)
{
  scanUSBforUpdate ("/home/test/tmp");
  return 0;
}
