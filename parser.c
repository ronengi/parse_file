#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

#include "container.h"
#include "error.h"

#define BUFMAX 2*MAXWORD
#define ISPLMIN(ch) (c == '-'   ||   c == '+')
#define FLUSH {  buffer[ind] = '\0';  flush();  }
#define ADD(ch, st) {  buffer[ind++] = (ch);  status = (st);  }

int flush();


static unsigned char buffer[BUFMAX];
static int ind = 0;
static enum {OUT, STR, NUM, DOT, FLOAT , MIN_PLS, MARK} status = OUT;


/*
  return values
  0 - normal
  1 - unidentified token
  2 - memory allocation error
  EOF - c was EOF
*/
int process(int c) {
  if (ind >= BUFMAX-1)    error("Error: buffer overflow!\n");
  if (c == EOF) {
    if (ind > 0)
      FLUSH;
    return EOF;
  }

  switch(status) {

  case OUT:
    if(isspace(c))         ;
    else if(isdigit(c))    {            ADD(c, NUM)                }
    else if(isalpha(c))    {            ADD(c, STR)                }
    else if(ISPLMIN(c))    {            ADD(c, MIN_PLS)            }
    else                   {            ADD(c, MARK);    FLUSH;    }
    break;

  case STR:
    if(isspace(c))         {  FLUSH                                }
    else if(isdigit(c))    {  FLUSH;    ADD(c, NUM);               }
    else if(isalpha(c))    {            ADD(c, STR);               }
    else if(ISPLMIN(c))    {  FLUSH;    ADD(c, MIN_PLS);           }
    else                   {  FLUSH;    ADD(c, MARK);    FLUSH;    }
    break;

  case MIN_PLS:
    if(isdigit(c))         {            ADD(c, NUM)                }
    else                   {  FLUSH;    return process(c);         }
    break;

  case NUM:
  case FLOAT:
    if(isspace(c))         {  FLUSH                                }
    else if(isdigit(c))    {            ADD(c, status)             }
    else if(isalpha(c))    {  FLUSH;    ADD(c, STR);               }
    else if(c == '.') {
      if(status == NUM)    {            ADD(c, DOT);               }
      if(status == FLOAT)  {  FLUSH;    ADD(c, MARK);    FLUSH;    }
    }
    else if(ISPLMIN(c))    {  FLUSH;    ADD(c, MIN_PLS);           }
    else                   {  FLUSH;    ADD(c, MARK);    FLUSH;    }
    break;

  case DOT:
    if(isdigit(c))         {            ADD(c, FLOAT)              }
    else                   {    --ind;    FLUSH;    ADD('.', MARK);  FLUSH;    return process(c);  }
    break;

  default:
    break;
  }

  return 0;
}


int flush() {
  int err = 0;

  switch(status) {

  case STR:
    add(TEXT, buffer);
    break;

  case NUM:
  case FLOAT:
    add(NUMBER, atof((char *)buffer));
    break;

  case MARK:
    add(P_MARK, buffer);
    break;

  default:
    err = 1;
    break;
  }

  ind = 0;
  status = OUT;

  return err;
}
