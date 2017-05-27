#include <stdio.h>

#include "parser.h"
#include "container.h"
#include "error.h"


int main (int argc, char **argv) {
  FILE *fp;
  int p;

  if (argc != 2)                             error("Usage: %s [FILE]\n", argv[0]);
  if ((fp = fopen(argv[1], "r")) == NULL)    error("Unable to open %s for reading!\n", argv[1]);

  while ((p = process(getc(fp))) != EOF   &&    p != 2)
    ;

  fclose(fp);

  if (p == 2)
    error("Error: there was a memory allocation error.\nProgram terminates.\n");

  print();    
  destruct();

  return 0;
}
