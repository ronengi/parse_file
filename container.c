#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>

#include "container.h"
#include "error.h"



typedef struct node_st *nodep; 
struct node_st {
  enum type_en type;
  union {
    double ndata;
    char sdata[MAXWORD];
  } data;
  nodep next;
};


static nodep head = NULL;
static nodep tail = NULL;

/*
  0 - normal
  1 - unknown token type
  2 - memory allocation failed
*/
int add(enum type_en type, ...) {
  va_list args;
  nodep new_node;

  if ((new_node = (nodep)malloc(sizeof(struct node_st))) == NULL)    /* can't allocate memory */
    return 2;
  new_node->type = type;
  new_node->next = NULL;

  va_start(args, type);
  switch (type) {
  case NUMBER:
    new_node->data.ndata = va_arg(args, double);
    break;
  case TEXT:
  case P_MARK:
    strcpy(new_node->data.sdata, va_arg(args, char *));
    break;
  default:    /* unknown token type */
    va_end(args);
    free(new_node);
    return 1;
    break;
  }
  va_end(args);

  if (head)
    tail = tail->next = new_node;
  else
    head = tail = new_node;

  return 0;
}

void print() {
  nodep cur;

  printf("LIST START:\n");

  for (cur = head; cur; cur = cur->next) {
    switch (cur->type) {
    case NUMBER:
      printf("%f -> ", cur->data.ndata);
      break;
    case TEXT:
      printf("%s -> ", cur->data.sdata);
      break;
    case P_MARK:
      printf("%s -> ", cur->data.sdata);
      break;
    default:
      printf("unknown -> ");
      break;
    }
    printf("\n");
  }
  printf("-\nLIST END\n");
}


void destruct() {
  nodep cur, next;

  for (cur = head; cur; cur = next) {
    next = cur->next;
    free(cur);
  }
}
