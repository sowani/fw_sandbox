#include <stdio.h>

#define dprintf(x) printf ("DEBUG: ");printf x

int main (void)
{
  int n = 1;
  dprintf (("test print\n"));
  dprintf (("test print %d\n", n));
  return (0);
}
