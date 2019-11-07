#include <stdio.h>
#include <signal.h>

static int count = 0;

void signalCB (int sig)
{
    int usbDetected = 0;
    if (sig == SIGUSR1)
    {
        /* USB insertion event detected. */
        usbDetected = 1;
		printf ("usb insert event detected.\n");
		count++;
    } else if (sig == SIGUSR2)
    {
        /* USB removal event detected. */
        usbDetected = 0;
		printf ("usb eject event detected.\n");
		count++;
    } else if (sig == SIGKILL)
    {
        //stopService();
    }
}

int main (void)
{
  signal (SIGUSR1, signalCB);
  signal (SIGUSR2, signalCB);

  printf ("waiting for usb event ...\n");
  while (count <= 6) {}
  return (0);
}
