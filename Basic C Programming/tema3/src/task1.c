#include "task1.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define size 200
#define sutica 100
#define precizie 1000
#define aproximare 10

secretariat *citeste_secretariat(const char *nume_fisier) {
  secretariat *secretariats = malloc(sizeof(*secretariats));
  secretariats->nr_studenti = 0;
  secretariats->studenti = malloc(secretariats->nr_studenti * sizeof(student));
  secretariats->nr_materii = 0;
  secretariats->materii = malloc(secretariats->nr_materii * sizeof(materie));
  secretariats->nr_inrolari = 0;
  secretariats->inrolari = malloc(secretariats->nr_inrolari * sizeof(inrolare));
  FILE *fisier = fopen(nume_fisier, "r");
  char *buffer = malloc(size * sizeof(char));
  fgets(buffer, size, fisier);
  int nrelev = 0;
  while (fgets(buffer, size, fisier) && buffer[0] <= '9' && buffer[0] >= '0') {
    nrelev++;
    student *new_students =
        realloc(secretariats->studenti, nrelev * sizeof(student));
    char *p = strtok(buffer, ",");
    int i = atoi(p);
    new_students[i].id = i;
    p = strtok(NULL, ",");
    p++;
    snprintf(new_students[i].nume, sizeof(new_students[i].nume), "%s", p);
    p = strtok(NULL, ",");
    new_students[i].an_studiu = atoi(p);
    p = strtok(NULL, ",");
    p++;
    new_students[i].statut = p[0];
    secretariats->studenti = new_students;
    secretariats->nr_studenti++;
  }
  int nrmat = 0;
  while (fgets(buffer, size, fisier) && buffer[0] <= '9' && buffer[0] >= '0') {
    char *newline = strchr(buffer, '\n');
    if (newline)
      *newline = 0;
    char *p = strtok(buffer, ",");
    int i = atoi(p);
    nrmat++;
    materie *new_materii =
        realloc(secretariats->materii, nrmat * sizeof(materie));
    new_materii[i].nume = malloc(sutica * sizeof(char));
    new_materii[i].nume_titular = malloc(sutica * sizeof(char));
    new_materii[i].id = i;
    p = strtok(NULL, ",");
    p++;
    strncpy(new_materii[i].nume, p, sizeof(p));
    p = strtok(NULL, "\r");
    p++;
    snprintf(new_materii[i].nume_titular, sutica, "%s", p);
    secretariats->materii = new_materii;
    secretariats->nr_materii++;
  }
  int nrinr = 0;
  while (fgets(buffer, size, fisier) && buffer[0] <= '9' && buffer[0] >= '0') {
    nrinr++;
    inrolare *new_inrolari =
        realloc(secretariats->inrolari, nrinr * sizeof(inrolare));
    char *p = strtok(buffer, ",");
    new_inrolari[nrinr - 1].id_student = atoi(p);
    p = strtok(NULL, ",");
    p++;
    new_inrolari[nrinr - 1].id_materie = atoi(p);
    float media = 0;
    for (int j = 0; j < 3; j++) {
      p = strtok(NULL, " ");
      new_inrolari[nrinr - 1].note[j] = (float)atof(p);
    }
    secretariats->inrolari = new_inrolari;
    secretariats->nr_inrolari++;
  }
  for (int j = 0; j < secretariats->nr_studenti; j++) {
    float media = 0, k = 0;
    for (int i = 0; i < secretariats->nr_inrolari; i++) {
      if (secretariats->inrolari[i].id_student == j) {
        for (int d = 0; d < 3; d++) {
          media += secretariats->inrolari[i].note[d];
        }
        k++;
      }
    }
    secretariats->studenti[j].medie_generala = media / k;
    int media_aprox =
        (int)(secretariats->studenti[j].medie_generala * precizie);
    if (media_aprox % aproximare > 4)
      secretariats->studenti[j].medie_generala =
          (float)((media_aprox / aproximare) + 1) / sutica;
    else
      secretariats->studenti[j].medie_generala =
          (float)(media_aprox / aproximare) / sutica;
  }
  free(buffer);
  fclose(fisier);
  return secretariats;
}

void adauga_student(secretariat *s, int id, char *nume, int an_studiu,
                    char statut, float medie_generala) {
  s->nr_studenti++;
  int nr_studenti = s->nr_studenti;
  s->studenti[nr_studenti - 1].id = id;
  s->studenti[nr_studenti - 1].an_studiu = an_studiu;
  s->studenti[nr_studenti - 1].statut = statut;
  s->studenti[nr_studenti - 1].medie_generala = medie_generala;
  snprintf(s->studenti[nr_studenti - 1].nume, sutica, "%s", nume);
}

void elibereaza_secretariat(secretariat **s) {
  free((*s)->studenti);

  for (int i = 0; i < (*s)->nr_materii; i++) {
    free((*s)->materii[i].nume);
    free((*s)->materii[i].nume_titular);
  }
  free((*s)->materii);

  free((*s)->inrolari);

  free(*s);
  *s = NULL;
}
