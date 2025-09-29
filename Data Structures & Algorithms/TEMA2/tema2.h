/* Bostangiu Luca-Nicolae - 311CB */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct sateliti {
    char *nume;
    int frecventa;
    struct sateliti *st;
    struct sateliti *dr;
} TSatelit;

typedef int (*TFCmp)(TSatelit* , TSatelit*);

typedef struct Heap {
    int nrMax, nrElem;
    TSatelit **v;
    TFCmp comp;
} THeap;

THeap* AlocaHeap(int nrMax, TFCmp comp);
int RelMinHeap(TSatelit *v1, TSatelit *v2);
// int RelMaxHeap(TSatelit v1, TSatelit v2);
void AfisareHeap(THeap *h, int pos);
void DistrugeHeap(THeap **h);

void InserareHeap(THeap *h,  TSatelit *s);
TSatelit* ExtragereHeap(THeap *h);
TSatelit* Arbore(THeap *h);
int InaltimeArbore(TSatelit *r);
void PrintArbore(FILE *g, TSatelit *rad);
void Decodificare(FILE *g, TSatelit *rad, char *cod);
int Codificare(TSatelit *rad, char *nume, char *cod);
void Freearbore(TSatelit **s);