/* Bostangiu Luca-Nicolae - 311CB */

#include "tema2.h"

THeap* parse(FILE *f)
{
  int n;
  char buffer[100];
  fgets(buffer, 100, f);
  n = atoi(buffer); // nrMax
  THeap *h = AlocaHeap(n, RelMinHeap);
  while (n) {
    TSatelit *s = (TSatelit*)malloc(sizeof(TSatelit));
    if(!s)
    return NULL;
    fgets(buffer, 100, f);
    char *p = strchr(buffer, '\n');
    if (p)
    (*p) = '\0';
    p = strtok(buffer, " ");
    s->frecventa = atoi(p);
    p = strtok(NULL, " ");
    s->nume = malloc(15*sizeof(char));
    if(!s->nume)
    return NULL;
    s->nume[0] = '\0';
    strcpy(s->nume, p);
    s->st = NULL;
    s->dr = NULL;
    InserareHeap(h, s);
    n--;
  }
  return h;
}

int main(int argc, char *argv[]) {
  int x = argc;
  x++;
  int nrexercitiu = argv[1][2] - '0';
  FILE *f = fopen(argv[2], "r");
  FILE *g = fopen(argv[3], "w");
  THeap *h = parse(f);
  TSatelit *rad = Arbore(h); // parsez si formez arborele pentru oricare exercitiu
  if (nrexercitiu == 1) {
    PrintArbore(g, rad);
  } else if (nrexercitiu == 2) { // citesc mai multe coduri si pentru fiecare, folosesc arborele ca sa le decodific inapoi in nume de sateliti.
    int n;
    char buffer[1000];
    fgets(buffer, 1000, f);
    n = atoi(buffer); // nr de codif
    while (n) {
      fgets(buffer, 1000, f);
      char *p = strchr(buffer, '\n');
      if (p)
      (*p) = '\0';
      Decodificare(g, rad, buffer);
      n--;
    }
  } else if (nrexercitiu == 3) { // invers ex 2
    int n;
    char buffer[1000];
    fgets(buffer, 1000, f);
    n = atoi(buffer); // nr de decodif
    char codfinal[1000] = "\n";
    while (n) {
      fgets(buffer, 1000, f);
      char *p = strchr(buffer, '\n');
      if (p)
      (*p) = '\0';
      char cod[100] = "";
      Codificare(rad, buffer, cod);
      strcat(codfinal, cod);
      n--;
    }
    fprintf(g, "%s \n", codfinal);
  } else if (nrexercitiu == 4) {
    int n;
    char buffer[1000];
    fgets(buffer, 1000, f);
    n = atoi(buffer); // nr de sateliti
    char cod1[1000] = "";
    fgets(buffer, 1000, f);
    char *p = strchr(buffer, '\n');
    if (p)
    (*p) = '\0';
    Codificare(rad, buffer, cod1);
    while (n-1) {
      fgets(buffer, 1000, f);
      char *p = strchr(buffer, '\n');
      if (p)
      (*p) = '\0';
      char cod2[1000] = "";
      char codcombinat[1000] = "";
      Codificare(rad, buffer, cod2);
      for (int i=0; i<(int)strlen(cod1)-1; i++) { // cel mai lung prefix comun
        if (cod1[i] != cod2[i])
        break;
        codcombinat[i] = cod1[i];
        codcombinat[i+1] = '\n';
      }
      strcpy(cod1, codcombinat);
      n--;
    }
    if (strcmp(cod1, "")) // verif daca exista un parinte comun diferit de radacikna
    Decodificare(g, rad, cod1);
    else
    fprintf(g, "%s \n", rad->nume);
  }
  // Decodif icare(rad, "00010");
  // Decodificare(rad, "1110011");
  // char cod[100] = "\n";
  // Codificare(rad, "B4", cod);
  // printf("%s \n", cod);
  Freearbore(&rad);
  DistrugeHeap(&h);
  fclose(f);
  fclose(g);
  return 0;
}