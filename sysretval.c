#include <stdio.h>
#include <stdlib.h>

int main (void)
{
  int n;
  n = system ("./test_script.sh");

  if (WEXITSTATUS(n) == 0)
    printf ("script succeeded\n");
  else
    printf ("n = %d, %d\n", n, WEXITSTATUS(n));

  return (0);
}
