#ifndef CONTAINER_H
#define CONTAINER_H


#define MAXWORD 50


enum type_en {NUMBER, TEXT, P_MARK};

int add(enum type_en type, ...);
void print();
void destruct();



#endif
