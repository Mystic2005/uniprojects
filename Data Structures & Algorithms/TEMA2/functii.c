/* Bostangiu Luca-Nicolae - 311CB */

#include "tema2.h"

// functii heap din lab6

THeap* AlocaHeap(int nrMax, TFCmp comp)
{
  THeap* h = (THeap*) malloc(sizeof(struct Heap));
  if (!h)
  return NULL;

  h->v = (TSatelit **) malloc(nrMax * sizeof(TSatelit*));
  if (!h->v) {
  free(h);
  return NULL;
  }

  h->nrMax = nrMax;
  h->nrElem = 0;
  h->comp = comp;

  return h;
}

int RelMinHeap(TSatelit *v1, TSatelit *v2)
{
  if (v1->frecventa != v2->frecventa)
    return v1->frecventa - v2->frecventa;
  else return strcmp(v1->nume, v2->nume);
}

void DistrugeHeap(THeap **h)
{
  free((*h)->v);
  free(*h);
  *h = NULL; 
}

// end functii lab 6

void InserareHeap(THeap *h, TSatelit *s)
{
  if (!h || !s || h->nrElem == h->nrMax)
  return;
  h->v[h->nrElem] = s;
  h->nrElem++;

  for (int i=h->nrElem-1; i>0; i--) { // parcurg de la final spre inceput prin parinti
    int parent = (i-1) / 2;
    if (h->comp(h->v[i], h->v[parent]) < 0) { // caut locatia potrivita
      TSatelit *aux = h->v[i];
      h->v[i] = h->v[parent];
      h->v[parent] = aux;
      i = parent+1;
    } else
    break; // poz potrivita
  }
}

TSatelit* ExtragereHeap(THeap *h)
{
  if (!h || !h->nrElem)
  return NULL;
  TSatelit* extr = h->v[0]; // retin radacina
  h->nrElem--;
  h->v[0] = h->v[h->nrElem];

  int i=0; // incep parcurgere din radacina
  while (1) {
    int st = i*2 + 1;
    int dr = i*2 + 2;
    int minim = i;
    // iau indicii copiilor si caut minimul. daca nu l gasesc inseamna ca e plasat corect
    if (st < h->nrElem && h->comp(h->v[st], h->v[minim]) < 0)
      minim = st;
    if (dr < h->nrElem && h->comp(h->v[dr], h->v[minim]) < 0)
      minim = dr;
    if (minim == i)
      break;
    TSatelit *aux = h->v[i];
    h->v[i] = h->v[minim];
    h->v[minim] = aux;
    i = minim;
  }
  return extr;
}

TSatelit* Arbore(THeap *h)
{
  if (!h)
  return NULL;
  while (h->nrElem != 1) {
    TSatelit *st = ExtragereHeap(h);
    TSatelit *dr = ExtragereHeap(h); // extrag cei mai mici 2 sateliti
    TSatelit *combinat = (TSatelit*)malloc(sizeof(TSatelit));
    combinat->frecventa = st->frecventa + dr->frecventa;
    int strlength = strlen(st->nume) + strlen(dr->nume) + 1;
    combinat->nume = malloc(strlength * sizeof(char));
    if (!combinat->nume)
    return NULL;
    combinat->nume[0] = '\0';
    strcat(combinat->nume, st->nume);
    strcat(combinat->nume, dr->nume);
    combinat->st = st;
    combinat->dr = dr; // ii combin si ii fac fii noului satelit
    InserareHeap(h, combinat);
  }
  return ExtragereHeap(h);
}

int InaltimeArbore(TSatelit *r)
{
  if (!r)
  return 0;
  if (InaltimeArbore(r->st) > InaltimeArbore(r->dr)) // adun maximul inaltimii subarburilor st/dr
  return 1 + InaltimeArbore(r->st); // ca sa nu adun de mai multe ori inaltimea subarborilor
  else
  return 1 + InaltimeArbore(r->dr);
}

void PrintNivel(FILE *g, TSatelit *r, int nivel)
{
  if (!r)
  return;
  if (nivel == 0)
    fprintf(g, "%d-%s ", r->frecventa, r->nume);
  else {
    PrintNivel(g, r->st, nivel-1);
    PrintNivel(g, r->dr, nivel-1); // recursiv pana ajung la nivelul potrivit
  }
}

void PrintArbore(FILE *g, TSatelit *rad)
{
  int height = InaltimeArbore(rad);
  for (int i=1; i<=height; i++) {
    PrintNivel(g, rad, i-1); // print la fiecare nivel de jos in sus
    fprintf(g, "\n");
  }
}

void Decodificare(FILE *g, TSatelit *rad, char *cod)
{
  if (!rad || !cod)
  return;
  TSatelit *curr = rad; // iterator ca sa retin radacina
  for (int i=0; i<(int)strlen(cod); i++) {
    if (cod[i] == '0' && curr->st) {
      curr = curr->st;
    } else if (cod[i] == '1' && curr->dr) {
      curr = curr->dr;
    } else { // daca nu exista copil st/dr dau print si ma intorc in radacina
      fprintf(g, "%s ", curr->nume);
      curr = rad;
      if (cod[i] == '0' && curr->st)
        curr = curr->st;
      else if (cod[i] == '1' && curr->dr)
        curr = curr->dr;
    }
  }
  if (!curr->st && !curr->dr) // verific daca e frunza
  fprintf(g, "%s ", curr->nume);
  fprintf(g, "\n");
}

int Codificare(TSatelit *rad, char *nume, char *cod)
{
  if (!rad)
  return 0;
  if (strcmp(rad->nume, nume) == 0) // l am gasit
  return 1;
  char codst[100], coddr[100];
  strcpy(codst, cod);
  strcat(codst, "0");
  strcpy(coddr, cod);
  strcat(coddr, "1");
  if (Codificare(rad->st, nume, codst)) { // ma intorc recursiv cu codul corect
    strcpy(cod,codst);
    return 1;
  }
  if (Codificare(rad->dr, nume, coddr)) {
    strcpy(cod,coddr);
    return 1;
  }
  return 0;
}

void Freearbore(TSatelit **s)
{
  if (!(*s))
  return;
  Freearbore(&(*s)->st); // free recursiv pe ramuri
  Freearbore(&(*s)->dr);
  free((*s)->nume);
  free(*s);
  *s = NULL;
}