#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>

#include "container.h"


void error(char *fmt, ...) {
  va_list args;
  va_start(args, fmt);
  vprintf(fmt, args);
  va_end(args);

  destruct();

  exit(EXIT_FAILURE);
}
