#include <inttypes.h>

#ifndef	ORDENACAO_H
#define	ORDENACAO_H
typedef void (*funcaoOrdenar)(uint16_t*, int);

void heapsort(uint16_t*, int);
void mergesort(uint16_t*, int);
void quicksort(uint16_t*, int);
#endif
